#include "tetramino.h"

const std::string Tetramino::TILE_TEXT_FILEPATH =
        "/home/stepan/Documents/code/sfml/img/tile.png";

// array of tetramino figures
// points which cell should be painted
const int Tetramino::FIGURES[FIGURES_COUNT][TILES_COUNT] = {
        {1, 3, 5, 7}, // I
        {2, 4, 5, 7}, // S
        {3, 5, 4, 6}, // Z
        {3, 5, 4, 7}, // T
        {2, 3, 5, 7}, // L
        {3, 5, 7, 6}, // J
        {2, 3, 4 ,5}, // O
    };

Tetramino::Tetramino(GameField &gameField, int index, const sf::Color &color)
{
    for (size_t tileIndex = 0; tileIndex < TILES_COUNT; tileIndex++)
    {
        sf::Vector2f tilePos;

        // convert local figure coordinates to global of game field
        tilePos.x = (Tetramino::FIGURES[index][tileIndex] % 2)
                * Tile::TEXTURE_WIDTH;
        tilePos.y = (Tetramino::FIGURES[index][tileIndex] / 2)
                * Tile::TEXTURE_HEIGHT;

        // create a new tile with given color and position
        tiles[tileIndex] = new Tile(TILE_TEXT_FILEPATH, gameField, color, tilePos);
    }
}

Tetramino::~Tetramino()
{
    for (size_t tileIndex = 0; tileIndex < TILES_COUNT; tileIndex++)
        if (tiles[tileIndex])
            delete tiles[tileIndex];
}

const Tile &Tetramino::getTile(int index)
{
    return *tiles.at(index);
}

// return sprite for drawing in window
const sf::Sprite &Tetramino::getTileSprite(int index)
{
    return tiles[static_cast<size_t>(index)]->getSprite();
}

// move tetramino along X-axis (horizontally)
bool Tetramino::moveH(int dx)
{
    // shift all tiles on given distance
    size_t tileIndex;
    bool beyond = false;
    for (tileIndex = 0; tileIndex < Tetramino::TILES_COUNT; tileIndex++)
    {
        beyond = !tiles[tileIndex]->moveOnField(dx, 0);
        if (beyond)
            break;
    }
    // tetramino not fit in game field
    if (beyond)
    {
        for (size_t offset = 0; offset < tileIndex; offset++)
            tiles[offset]->moveOnField(-dx, 0);
    }

    return !beyond;
}

// move tetramino along Y-axis(vertically)
bool Tetramino::moveV(int dy)
{
    // shift all tiles on given distance
    size_t tileIndex;
    bool beyond = false;
    for (tileIndex = 0; tileIndex < Tetramino::TILES_COUNT; tileIndex++)
    {
        beyond = !tiles[tileIndex]->moveOnField(0, dy);
        if (beyond)
            break;
    }
    if (beyond)
    {
        for (size_t offset = 0; offset < tileIndex; offset++)
            tiles[offset]->moveOnField(0, -dy);
    }

    return !beyond;
}

// rotate tetramino around center tile (with 1 index)
bool Tetramino::rotate(const GameField *gameField)
{
    sf::Vector2f rotCenter = tiles.at(1)->getPosition();

    std::array<sf::Vector2f, 4> newPos;
    bool beyond = false;
    for (size_t tileIndex = 0; tileIndex < TILES_COUNT; tileIndex++)
    {
        // using linear algebra's formula
        int dx = tiles[tileIndex]->getPosition().x - rotCenter.x;
        int dy = tiles[tileIndex]->getPosition().y- rotCenter.y;

        newPos[tileIndex] = sf::Vector2f(rotCenter.x - dy,
                            rotCenter.y + dx);
        beyond = !gameField->isInField(Tile::getCellCoords(newPos[tileIndex]))
                || !gameField->isCellEmpty(Tile::getCellCoords(newPos[tileIndex]));

        if (beyond)
            break;
    }

    if (!beyond)
    {
        for (size_t tileIndex = 0; tileIndex < TILES_COUNT; tileIndex++)
            tiles[tileIndex]->setPosition(newPos[tileIndex]);
    }

    return !beyond;
}

// fragmentation tetramino on separate tiles and pinning them on game field
void Tetramino::parcelling()
{
    for (size_t tileIndex = 0; tileIndex < TILES_COUNT; tileIndex++)
    {
        tiles[tileIndex]->pinOnField();
        tiles[tileIndex] = nullptr;
    }
}
