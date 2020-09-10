#include "tile.h"

const sf::Color Tile::COLORS[COLORS_COUNT] = {
    sf::Color::Blue,
    sf::Color(160, 32, 240),  // purple
    sf::Color::Red,
    sf::Color::Green,
    sf::Color::Yellow,
    sf::Color::Cyan,
    sf::Color(255, 165, 0),  // orange
};

Tile::Tile(const std::string &filepath, GameField &gf, sf::Color col,
           sf::Vector2f pos) : color(col), position(pos)
{
    gameField = &gf;
    texture.loadFromFile(filepath);

    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, TEXTURE_WIDTH, TEXTURE_HEIGHT));

    sprite.setColor(color);
    sprite.setPosition(position);
}

const sf::Sprite & Tile::getSprite() const
{
    return sprite;
}

bool Tile::moveH(int dx)
{
    position.x += dx * Tile::TEXTURE_WIDTH;
    if ((!gameField->isInField(getCellCoords(position)))
            || (!gameField->isCellEmpty(getCellCoords(position))))
    {
        position = sprite.getPosition();
        return false;
    }
    else
    {
        sprite.setPosition(position);
        return true;
    }
}

bool Tile::moveV(int dy)
{
    position.y += dy * Tile::TEXTURE_HEIGHT;
    if ((!gameField->isInField(getCellCoords(position)))
            || (!gameField->isCellEmpty(getCellCoords(position))))
    {
        position = sprite.getPosition();
        return  false;
    }
    else
    {
        sprite.setPosition(position);
        return true;
    }
}

const sf::Vector2f &Tile::getPosition() const
{
    return position;
}

void Tile::setPosition(const sf::Vector2f &pos)
{
    position = pos;
    sprite.setPosition(position);
}

sf::Vector2f Tile::getCellCoords(const sf::Vector2f &pos)
{
    //std::cout << "Global(" << pos.x << ", " << pos.y << ")\n";
    return sf::Vector2f(pos.x / Tile::TEXTURE_WIDTH,
                        pos.y / Tile::TEXTURE_HEIGHT);
}

// fill its own location on game field
void Tile::pinOnField()
{
    gameField->fillCell(getCellCoords(position), *this);
}
