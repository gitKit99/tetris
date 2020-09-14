#include "tile.h"
#include <iostream>

// tiles possible colors
const sf::Color Tile::COLORS[COLORS_COUNT] = {
    sf::Color::Blue,
    sf::Color(160, 32, 240),  // purple
    sf::Color::Red,
    sf::Color::Green,
    sf::Color::Yellow,
    sf::Color::Cyan,
    sf::Color(255, 165, 0),  // orange
};

Tile::Tile(const std::string &filepath, GameField &gf, sf::Color color,
           sf::Vector2f position) : gameField(&gf)
{
    // init texture by loading from given file
    texture.loadFromFile(filepath);
    this->setTexture(texture);

    this->setTextureRect(sf::IntRect(0, 0, TEXTURE_WIDTH, TEXTURE_HEIGHT));
    this->setColor(color);
    this->setPosition(position);
}

const sf::Sprite & Tile::getSprite() const
{
    return *this;
}

// move tile sprite in game field
// return true, if this action can be done
bool Tile::moveOnField(int dx, int dy)
{
    sf::Vector2f newPos(this->getPosition()); // copy current position

    // shift new position on given values
    // vertically (dy) or horizontally(dx)
    // multiplaying on texture size (field cell size)
    newPos.x += dx * TEXTURE_WIDTH;
    newPos.y += dy * TEXTURE_HEIGHT;

    // check if new position is on field and if its cell isn't already busy
    if (gameField->isInField(getCellCoords(newPos))
            && gameField->isCellEmpty(getCellCoords(newPos)))
    {
        this->setPosition(newPos);
        return true;
    }
    else return false;
}

const sf::Vector2f &Tile::getPos() const
{
    return this->getPosition();
}

void Tile::setPos(const sf::Vector2f &position)
{
    this->setPosition(position);
}

// return relative cell coordinates on game field
sf::Vector2f Tile::getCellCoords(const sf::Vector2f &pos)
{
    return sf::Vector2f(pos.x / TEXTURE_WIDTH,
                        pos.y / TEXTURE_HEIGHT);
}

// fill its own location on game field
void Tile::pinOnField()
{
    this->gameField->fillCell(getCellCoords(this->getPosition()), *this);
}
