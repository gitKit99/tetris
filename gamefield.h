#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <SFML/Graphics.hpp>

class Tile;
class DrawingSystem;

class GameField
{
    int width;
    int height;

    sf::RectangleShape fieldBorder;
    const static int BORDER_THICKNESS = 5;

    int highestTileLevel;

public:
    enum class FieldSign
    {
       EMPTY,
       BUSY
    };
    GameField(int w, int h);
    ~GameField();
    bool isInField(const sf::Vector2f &pos) const;
    bool isCellEmpty(const sf::Vector2f &coords) const;
    void fillCell(sf::Vector2f coords, Tile &tile);
    int getHighestLevel();
    void checkRowsFilling(DrawingSystem &ds);

    const sf::RectangleShape & getBorderShape() const;

private:
    struct FieldCell
    {
        FieldSign sign = FieldSign::EMPTY;
        Tile *tilePtr = nullptr;

        FieldCell& operator=(FieldCell &other);
    };

    FieldCell **field;
};

#endif // GAMEFIELD_H
