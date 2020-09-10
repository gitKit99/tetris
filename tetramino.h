#ifndef TETRAMINO_H
#define TETRAMINO_H

#include<array>
#include <iostream>

#include "tile.h"

class Tetramino
{
    int figureIndex;
    std::array<Tile*, 4> tiles;

public:
    static const int FIGURES_COUNT = 7;
    static const int TILES_COUNT = 4;
    static const std::string TILE_TEXT_FILEPATH;
    static const int FIGURES[FIGURES_COUNT][TILES_COUNT];
    Tetramino(GameField &gamefield, int index, const sf::Color &color);
    ~Tetramino();
    const Tile& getTile(int index);
    const sf::Sprite& getTileSprite(int index);
    bool moveH(int dx);
    bool moveV(int dy);
    bool rotate(const GameField *gameField);
    void parcelling();
};

#endif // TETRAMINO_H
