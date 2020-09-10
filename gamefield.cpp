#include "gamefield.h"
#include "tile.h"
#include "drawingsystem.h"

#include <iostream>

GameField::GameField(int w, int h) : width(w), height(h)
{
    field = new FieldCell*[height];

    for (int row = 0; row < height; row++)
        field[row] = new FieldCell[width];

    fieldBorder = sf::RectangleShape(sf::Vector2f(width * 18.f - BORDER_THICKNESS, height * 18.f));

    fieldBorder.setOutlineThickness(BORDER_THICKNESS);
    fieldBorder.setOutlineColor(sf::Color::Black);
    fieldBorder.setFillColor(sf::Color(0, 0, 0, 0));
    fieldBorder.move(BORDER_THICKNESS, 0);

    highestTileLevel = height - 1;
}

GameField::~GameField()
{
    for (int row = 0; row < height; row++)
        delete field[row];

    delete field;
}

bool GameField::isInField(const sf::Vector2f &pos) const
{
    //std::cout << "Cell position(" << pos.x << ", " << pos.y << ")\n";
    if ((pos.x >= 0) && (pos.y >= 0) && (pos.x < width) && (pos.y < height))
        return true;

    return false;
}

bool GameField::isCellEmpty(const sf::Vector2f &coords) const
{
    return field[static_cast<int>(coords.y)][static_cast<int>(coords.x)].sign
            == FieldSign::EMPTY;
}

void GameField::fillCell(sf::Vector2f coords, Tile &tile)
{
    int row = static_cast<int>(coords.y);
    int clmn = static_cast<int>(coords.x);

    field[row][clmn].sign = FieldSign::BUSY;
    field[row][clmn].tilePtr = &tile;

    if (row < highestTileLevel)
        highestTileLevel = row;
}

int GameField::getHighestLevel()
{
    return highestTileLevel;
}

void GameField::checkRowsFilling(DrawingSystem &ds)
{
    std::cout << "Checking\n";
    int sourceRow = height - 1;
    for (int row = height - 1; row > 0; row--)
    {
        int tilesCount = 0;
        for (int clmn = 0; clmn < width; clmn++)
        {
            if (field[row][clmn].sign == FieldSign::BUSY)
                tilesCount++;

            // tiles reassignement
            //std::cout << "Assignment\n";

             if (sourceRow != row)
             {
                 if (field[sourceRow][clmn].sign == FieldSign::BUSY)
                     ds.delItemByRef(*field[sourceRow][clmn].tilePtr);

                 field[sourceRow][clmn] = field[row][clmn];

                 if (field[sourceRow][clmn].sign == FieldSign::BUSY)
                 {
                     sf::Vector2f newTileCoords(clmn * Tile::TEXTURE_WIDTH,
                                                sourceRow * Tile::TEXTURE_HEIGHT);
                     field[sourceRow][clmn].tilePtr->setPosition(newTileCoords);
                 }
             }
        }

        if (tilesCount < width)
            sourceRow--;
    }

    /*for (int row = height - 1; row <= highestTileLevel; row--)
    {
        bool rowFull = true;
        for (int clmn = 0; clmn < width; clmn++)
        {
            if (field[row][clmn].sign == FieldSign::EMPTY)
            {
                rowFull = false;
                break;
            }
        }

        if (rowFull)
        {
            for (int clmn = 0; clmn < width; clmn++)
            {
                FieldCell &clearedCell = field[row][clmn];
                clearedCell.sign = FieldSign::EMPTY;
                delete clearedCell.tilePtr;

                if ((row != highestTileLevel)
                        && (field[row - 1][clmn].sign == FieldSign::BUSY))
                {
                    FieldCell &shiftedCell = field[row - 1][clmn];
                    bool moved = shiftedCell.tilePtr->moveV(1);

                    if (!moved)
                        std::cout << "Something went wrong" << std::endl;

                    clearedCell.sign = shiftedCell.sign;
                    clearedCell.tilePtr = shiftedCell.tilePtr;

                    shiftedCell.sign = FieldSign::EMPTY;
                    shiftedCell.tilePtr = nullptr;
                }
            }
        }
    }*/
}

const sf::RectangleShape &GameField::getBorderShape() const
{
    return fieldBorder;
}

GameField::FieldCell &GameField::FieldCell::operator=(GameField::FieldCell &other)
{
    if (this == &other)
        return *this;

    if (this->tilePtr)
    {
        delete this->tilePtr;
        std::cout << "DELETED\n";
        this->tilePtr = nullptr;
    }

    this->sign = other.sign;
    this->tilePtr = other.tilePtr;

    // clear other
    other.sign = FieldSign::EMPTY;
    other.tilePtr = nullptr;

    return *this;
}
