#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include <string>

#include "gamefield.h"

// represents one tile of tetramino
class Tile
{
    sf::Color color = sf::Color::Blue;
    sf::Vector2f position;
    sf::Sprite sprite;
    sf::Texture texture;

    GameField *gameField;

public:
    static const int TEXTURE_WIDTH = 18; // width and
    static const int TEXTURE_HEIGHT  = 18; // height of tile texture
    static const int COLORS_COUNT = 7;

    static const sf::Color COLORS[7];

    Tile(const std::string &filepath, GameField &gf,  sf::Color color = sf::Color::Blue,
         sf::Vector2f pos = sf::Vector2f(0.f,0.f));
    const sf::Sprite& getSprite() const;
    bool moveH(int dx);
    bool moveV(int dy);
    const sf::Vector2f& getPosition() const;
    void setPosition(const sf::Vector2f &pos);
    static sf::Vector2f getCellCoords(const sf::Vector2f &pos);
    void pinOnField();
};

#endif // TILE_H
