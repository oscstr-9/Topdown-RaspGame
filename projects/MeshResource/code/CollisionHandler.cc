#include "CollisionHandler.h"

void CollisionHandler::handleCollisions(Tilegrid* tilegrid)
{
    if(tilesToUpdate.empty())
    {
        return;
    }

    Tile* tile;
    // check each tile against walls first before checking any other collision
    for(int i = 0; i < tilesToUpdate.size(); i++)
    {
        tile = tilesToUpdate[i];
        // check testObjects
        for(int j = 0; j < tile->gameObjects.size(); j++)
        {
            // check against walls
            for(int k = 0; k < tile->neighborWalls.size(); k++)
            {
                // check aabb
                if(AABBCollision(tile->gameObjects[j]->pos, tile->gameObjects[j]->size, tile->neighborWalls[k].worldPos, tile->neighborWalls[k].size))
                {
                    //std::cout << "TestObject is colliding with wall, moving to previous pos" << std::endl;
                    //tile->gameObjects[j]->pos = tile->gameObjects[j]->previousPos;
                    // TODO: check which direction to move back to
                    VectorMath2 objectPos = tile->gameObjects[j]->pos;
                    float objectSize = tile->gameObjects[j]->size * 1.9;
                    VectorMath2 wallPos = tile->neighborWalls[k].worldPos;
                    float wallSize = tile->neighborWalls[k].size * 1.9;

                    VectorMath2 intersectionDepth(0, 0);
                    //intersectionDepth.x = 
                    

                    VectorMath2 direction = tile->neighborWalls[k].pos - tile->pos;
                    // vertical
                    if(abs(direction.y) && !abs(direction.x))
                    {
                        std::cout << "vertical" << std::endl;
                        intersectionDepth.y = (objectPos.y + objectSize) - (wallPos.y + wallSize);
                    }
                    // horizontal
                    else if(!abs(direction.y) && abs(direction.x))
                    {
                        std::cout << "horizontal" << std::endl;
                        intersectionDepth.x = (objectPos.x + objectSize) - (wallPos.x + wallSize);
                    }
                    // diagonal
                    else
                    {
                        std::cout << "diagonal" << std::endl;
                        intersectionDepth.y = (objectPos.y + objectSize) - (wallPos.y + wallSize);
                        intersectionDepth.x = (objectPos.x + objectSize) - (wallPos.x + wallSize);
                    }
                    intersectionDepth = intersectionDepth * (objectSize / 4);
                    tile->gameObjects[j]->pos = tile->gameObjects[j]->pos + intersectionDepth;

                }
            }
        }
    }
    // move object to new ground tile corresponding to its pos if necessary
    for(int i = 0; i < tilesToUpdate.size(); i++)
    {
        moveObjectsToNeighborOfTile(tilesToUpdate[i], tilegrid);
    }
    // check all the other collisions
    // enemy vs player
}
bool CollisionHandler::AABBCollision(VectorMath2 pos1, float size1, VectorMath2 pos2, float size2)
{
    size1 = size1 * 1.9;
    size2 = size2 * 1.9;
    if(pos1.x + size1 > pos2.x && pos2.x + size2 > pos1.x &&
       pos1.y + size1 > pos2.y && pos2.y + size2 > pos1.y)
    {
        return true;
    }

    return false;
}
bool CollisionHandler::pointInsideTile(VectorMath2 pointPos, VectorMath2 tilePos, float tileSize)
{
    // add all points necessary before doing the math/comparisons
    // tilePos.x = tilePos.x * tileSize;
    // tilePos.y = tilePos.y * tileSize;

    float bottomLeftX, bottomLeftY, topRightX, topRightY;
    bottomLeftX = tilePos.x - tileSize/2;
    bottomLeftY = tilePos.y - tileSize/2;
    topRightX = tilePos.x + tileSize/2;
    topRightY = tilePos.y + tileSize/2;

    if(pointPos.x >= bottomLeftX && pointPos.x <= topRightX && 
        pointPos.y >= bottomLeftY && pointPos.y <= topRightY)
    {
        // point is inside tile
        return true;
    }

    return false;
}

// returns true if the tile was added to list
bool CollisionHandler::updateListOfTiles(Tile* tile, Tilegrid* tilegrid)
{
    for(int j = 0; j < tilesToUpdate.size(); j++)
    {
        if(tilesToUpdate[j]->pos == tilegrid->tileInPos.at(tile->pos).pos)
        {
            return false;
        }
        if(tilesToUpdate[j]->gameObjects.empty())
        {	
            tilesToUpdate.erase(tilesToUpdate.begin() + j);
            j--;
        }
    }

    // add tile to list if tile.pos was not found in tilesToUpdate[j].pos
    tilesToUpdate.push_back(&tilegrid->tileInPos.at(tile->pos));
    return true;
}

// makes sure all objects from this tile is always inside its corresponding tile
void CollisionHandler::moveObjectsToNeighborOfTile(Tile* tile, Tilegrid* tilegrid)
{
    for(int k = 0; k < tile->gameObjects.size(); k++)
    {
        GameObject* object = tile->gameObjects[k];

        if(pointInsideTile(object->pos, tile->worldPos, tile->size))
        {
            // If inside, do nothing.
        }

        else // if outside, move object to new corresponding ground tile
        {
            for(int i = 0; i < tile->neighborGround.size(); i++)
            {
                Tile* groundTile = &tile->neighborGround[i];

                // find corresponding ground tile
                if(pointInsideTile(object->pos, groundTile->worldPos, groundTile->size))
                {
                    // remove old object
                    for(int j = 0; j < tile->gameObjects.size(); j++)
                    {
                        if(object->ID = tile->gameObjects[j]->ID)
                        {
                            tile->gameObjects.erase(tile->gameObjects.begin() + j);
                            k--;
                        }
                    }

                    // add new object
                    tilegrid->tileInPos.at(groundTile->pos).gameObjects.push_back(object);
                    //std::cout << "TestObject has moved to another ground tile" << std::endl;
                    
                    // -------- update the tilesToUpdate list --------
                    if(updateListOfTiles(&tilegrid->tileInPos.at(groundTile->pos), tilegrid))
                    {
                        //std::cout << "Tile has been added to tilesToUpdate" << std::endl;
                    }

                    break;
                }
            }
        }
    }
}