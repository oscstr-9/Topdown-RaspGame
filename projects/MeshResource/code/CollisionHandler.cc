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
                    tile->gameObjects[j]->pos = tile->gameObjects[j]->previousPos;
                }
            }
        }
    }
    // move object to new ground tile corresponding to its pos if necessary
    for(int i = 0; i < tilesToUpdate.size(); i++)
    {
        moveObjectsToNeighborOfTile(tilesToUpdate[i], tilegrid);
    }
    
    // -------- enemy vs player --------
    // find player inside tile and remove it from gameObject list
    GameObject* player;
    for(int i = 0; i < tilegrid->playerTile->gameObjects.size(); i++)
    {
        if(tilegrid->playerTile->gameObjects[i]->objectType == ObjectType::PLAYER)
        {
            player = tilegrid->playerTile->gameObjects[i];
            tilegrid->playerTile->gameObjects.erase(tilegrid->playerTile->gameObjects.begin() + i);
        }
    }

    // check inside its own tile
    for(int i = 0; i < tilegrid->playerTile->gameObjects.size(); i++)
    {
        if(AABBCollision(player->pos, player->size, tilegrid->playerTile->gameObjects[i]->pos, tilegrid->playerTile->gameObjects[i]->size))
        {
            //std::cout << "Player has collided with an enemy" << std::endl;
        }
    }

    // check against neighbor ground
    for(int i = 0; i < tilegrid->playerTile->neighborGround.size(); i++)
    {
        // check against enemies
        tile = &tilegrid->tileInPos.at(tilegrid->playerTile->neighborGround[i].pos);
        for(int j = 0; j < tile->gameObjects.size(); j++)
        {
            if(AABBCollision(player->pos, player->size, tile->gameObjects[j]->pos, tile->gameObjects[j]->size))
            {
                //std::cout << "Player has collided with an enemy" << std::endl;
            }
        }
        
    }
    // put back player into gameObject list
    tilegrid->playerTile->gameObjects.push_back(player);
    // --------
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
    bottomLeftX = tilePos.x - tileSize;
    bottomLeftY = tilePos.y - tileSize;
    topRightX = tilePos.x + tileSize;
    topRightY = tilePos.y + tileSize;

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
                    if(object->objectType == ObjectType::PLAYER)
                    {
                        tilegrid->playerTile = &tilegrid->tileInPos.at(groundTile->pos);
                    }
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

void CollisionHandler::checkRayAgainstEnemies(VectorMath2 start, VectorMath2 direction, Tilegrid* tilegrid)
{
    direction.Normalize();

    // -------- check inside player tile first --------
    GameObject* player;
    for(int i = 0; i < tilegrid->playerTile->gameObjects.size(); i++)
    {
        if(tilegrid->playerTile->gameObjects[i]->objectType == ObjectType::PLAYER)
        {
            player = tilegrid->playerTile->gameObjects[i];
            tilegrid->playerTile->gameObjects.erase(tilegrid->playerTile->gameObjects.begin() + i);
        }
    }
    for(int i = 0; i < tilegrid->playerTile->gameObjects.size(); i++)
    {
        VectorMath2 pointInTile = start;
        pointInTile = pointInTile - direction * tilegrid->playerTile->size;
        while(pointInsideTile(pointInTile, tilegrid->playerTile->worldPos, tilegrid->playerTile->size))
        {
            if(pointInsideTile(pointInTile, tilegrid->playerTile->gameObjects[i]->pos, tilegrid->playerTile->gameObjects[i]->size))
            {
                std::cout << "Raycast hit an enemy" << std::endl;
                tilegrid->playerTile->gameObjects.erase(tilegrid->playerTile->gameObjects.begin() + i);
                i--;
                if(tilegrid->playerTile->gameObjects.empty())
                {
                    break;
                }
            }
            pointInTile = pointInTile + direction * (tilegrid->playerTile->gameObjects[i]->size / 3);
        }
    }
    // --------

    // -------- walk through the tiles until ray is inside a wall --------
    Tile* nextTile = nextTileInDirection(tilegrid->playerTile, direction, &start, tilegrid);
    // move outside of player tile
    while(nextTile->pos == tilegrid->playerTile->pos)
    {
        nextTile = nextTileInDirection(tilegrid->playerTile, direction, &start, tilegrid);
    }
    // check the rest of the tiles in ray direction
    while(true)
    {
        if(nextTile->type == Type::WALL)
        {
            std::cout << "Raycast hit a wall" << std::endl;
            break;
        }
        // if enemy is inside, check if ray is inside the enemy
        for(int i = 0; i < nextTile->gameObjects.size(); i++)
        {
            // have points be more frequent inside tile to see if ray hit enemy
            VectorMath2 pointInTile = nextTile->worldPos;
            pointInTile = pointInTile - direction * nextTile->size;
            while(pointInsideTile(pointInTile, nextTile->worldPos, nextTile->size))
            {
                if(pointInsideTile(pointInTile, nextTile->gameObjects[i]->pos, nextTile->gameObjects[i]->size))
                {
                    std::cout << "Raycast hit an enemy" << std::endl;
                    nextTile->gameObjects.erase(nextTile->gameObjects.begin() + i);
                    i--;
                    if(nextTile->gameObjects.empty())
                    {
                        for(int j = 0; j < tilesToUpdate.size(); j++)
                        {
                            if(tilesToUpdate[j]->pos == nextTile->pos)
                            {
                                tilesToUpdate.erase(tilesToUpdate.begin() + j);
                                j--;
                            }
                        }
                        break;
                    }
                }
                pointInTile = pointInTile + direction * (nextTile->gameObjects[i]->size / 3);
            }
            
        }
        nextTile = nextTileInDirection(nextTile, direction, &start, tilegrid);
    }
    // --------
    tilegrid->playerTile->gameObjects.push_back(player);
}
Tile* CollisionHandler::nextTileInDirection(Tile* currentTile, VectorMath2 direction, VectorMath2* rayStart, Tilegrid* tilegrid)
{
    Tile* nextTile;

    VectorMath2 nextPoint;
    VectorMath2 nextTilePos = currentTile->pos;
    float tileSize = currentTile->size * 2;
    nextPoint = *rayStart;

    if(direction.x > 0)
    {
        // +=
        nextPoint.x += direction.x * tileSize;
        if(pointInsideTile(nextPoint, tilegrid->tileInPos.at(VectorMath2(nextTilePos.x + 1, nextTilePos.y)).worldPos, currentTile->size))
        {
            nextTilePos.x++;
        }
    }
    else
    {
        // -=
        nextPoint.x -= direction.x * tileSize;
        if(pointInsideTile(nextPoint, tilegrid->tileInPos.at(VectorMath2(nextTilePos.x - 1, nextTilePos.y)).worldPos, currentTile->size))
        {
            nextTilePos.x--;
        }
    }
    if(direction.y > 0)
    {
        // +=
        nextPoint.y += direction.y * tileSize;
        if(pointInsideTile(nextPoint, tilegrid->tileInPos.at(VectorMath2(nextTilePos.x, nextTilePos.y + 1)).worldPos, currentTile->size))
        {
            nextTilePos.y++;
        }
    }
    else
    {
        // -=
        nextPoint.y -= direction.y * tileSize;
        if(pointInsideTile(nextPoint, tilegrid->tileInPos.at(VectorMath2(nextTilePos.x, nextTilePos.y - 1)).worldPos, currentTile->size))
        {
            nextTilePos.y--;
        }
    }

    rayStart->x = nextPoint.x;
    rayStart->y = nextPoint.y;

    nextTile = &tilegrid->tileInPos.at(nextTilePos);

    return nextTile;
}