#ifndef DRAWINGSYSTEM_H
#define DRAWINGSYSTEM_H

#include <list>
#include <iterator>

class Tile;

class DrawingSystem
{
public:
    std::list<const Tile*> drawable;
    DrawingSystem();

    void delItemByRef(const Tile&);
};

#endif // DRAWINGSYSTEM_H
