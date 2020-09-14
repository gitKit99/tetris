#include "tile.h"
#include <iostream>

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

bool Tile::moveOnField(int dx, int dy)
{
    sf::Vector2f pos(this->getPosition());
    pos.x += dx * TEXTURE_WIDTH;
    pos.y += dy * TEXTURE_HEIGHT;

    if ((!gameField->isInField(getCellCoords(pos)))
            || (!gameField->isCellEmpty(getCellCoords(pos))))
    {
        return false;
    }
    else {
        this->setPosition(pos);
        return true;
    }
}

/*bool Tile::moveH(int dx)
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
}*/

const sf::Vector2f &Tile::getPos() const
{
    return this->getPosition();
}

void Tile::setPos(const sf::Vector2f &position)
{
    this->setPosition(position);
}

sf::Vector2f Tile::getCellCoords(const sf::Vector2f &pos)
{
    //std::cout << "Global(" << pos.x << ", " << pos.y << ")\n";
    return sf::Vector2f(pos.x / TEXTURE_WIDTH,
                        pos.y / TEXTURE_HEIGHT);
}

// fill its own location on game field
void Tile::pinOnField()
{
    this->gameField->fillCell(getCellCoords(this->getPosition()), *this);
}
