#include "CollisionHandler.h"

void CollisionHandler::handleCollisions()
{
    if(tilesToUpdate.empty())
    {
        return;
    }

    Tile* tile;
    // check each tile
    for(int i = 0; i < tilesToUpdate.size(); i++)
    {
        tile = tilesToUpdate[i];
        // check testObjects
        for(int j = 0; j < tile->testObjects.size(); j++)
        {
            // check against walls
            for(int k = 0; k < tile->neighborWalls.size(); k++)
            {
                // check aabb
                if(AABBCollision(tile->testObjects[j]->pos, tile->testObjects[j]->size, tile->neighborWalls[k].pos, tile->neighborWalls[k].size))
                {
                    std::cout << "TestObject is colliding with wall" << std::endl;
                }
            }
        }
    }
}
bool CollisionHandler::AABBCollision(Pos pos1, float size1, Pos pos2, float size2)
{
    if(pos1.x + size1 >= pos2.x && pos2.x + size2 >= pos1.x &&
       pos1.y + size1 >= pos2.y && pos2.y + size2 >= pos1.y)
    {
        return true;
    }

    return false;
}
bool CollisionHandler::pointInsideTile(Pos pointPos, Pos tilePos, float tileSize)
{
    // TODO: add all points necessary befor doing the math/comparisons
    Pos bottomLeft;

    return false;
}