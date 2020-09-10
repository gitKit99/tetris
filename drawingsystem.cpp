#include "drawingsystem.h"

DrawingSystem::DrawingSystem()
{

}

void DrawingSystem::delItemByRef(const Tile &item)
{
    for (auto it = drawable.begin(); it != drawable.end(); it++)
    {
        if (*it == &item)
        {
            drawable.erase(it);
            break;
        }
    }
}
