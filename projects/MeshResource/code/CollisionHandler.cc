#include "CollisionHandler.h"

bool CollisionHandler::hasCollidedWithWall(Tilegrid* tilegrid, VectorMath2 objectPos, float objectSize, VectorMath2 tilePos)
{
    // check all 8 neighbors
    for(int neighborTileY = tilePos.y - 1; neighborTileY <= tilePos.y + 1; neighborTileY++)
    {
        for(int neighborTileX = tilePos.x - 1; neighborTileX <= tilePos.x + 1; neighborTileX++)
        {
            if(VectorMath2(neighborTileX, neighborTileY) == tilePos)
                continue;
            if(tilegrid->tiles[neighborTileY][neighborTileX].type == Type::WALL)
            {
                // TODO: change from AABB to circle square collision
                if(AABBCollision(objectPos, objectSize, tilegrid->tiles[neighborTileY][neighborTileX].worldPos, tilegrid->tiles[neighborTileY][neighborTileX].size))
                {
                    return true;
                }
            }
        }
    }
    return false;
}
bool CollisionHandler::AABBCollision(VectorMath2 pos1, float size1, VectorMath2 pos2, float size2)
{
    pos1.x -= size1/2;
    pos1.y -= size1/2;
    pos2.x -= size2/2;
    pos2.y -= size2/2;
    if(pos1.x + size1 > pos2.x && pos2.x + size2 > pos1.x &&
       pos1.y + size1 > pos2.y && pos2.y + size2 > pos1.y)
    {
        return true;
    }

    return false;
}
void CollisionHandler::updateTilePos(GameObject* object, Tilegrid* tilegrid)
{
    // if not inside tile anymore, move object to the new tile
    if(!pointInsideTile(object->pos, tilegrid->tiles[object->tilePos.y][object->tilePos.x].worldPos, tilegrid->tileSize))
    {
        VectorMath2 direction = object->pos - tilegrid->tiles[object->tilePos.y][object->tilePos.x].worldPos;
        if(direction.y > 0)
        {
            // 5 left to check
            if(direction.x > 0)
            {
                // 3 to check (up right)
                if(pointInsideTile(object->pos, tilegrid->tiles[object->tilePos.y][object->tilePos.x + 1].worldPos, tilegrid->tileSize))
                {
                    tilegrid->moveToTile(object, VectorMath2(object->tilePos.x + 1, object->tilePos.y));
                }
                else if(pointInsideTile(object->pos, tilegrid->tiles[object->tilePos.y + 1][object->tilePos.x].worldPos, tilegrid->tileSize))
                {
                    tilegrid->moveToTile(object, VectorMath2(object->tilePos.x, object->tilePos.y + 1));
                }
                else // it's inside upper right
                {
                    tilegrid->moveToTile(object, VectorMath2(object->tilePos.x + 1, object->tilePos.y + 1));
                }
            }
            else if(direction.x < 0)
            {
                // 3 to check (up left)
                if(pointInsideTile(object->pos, tilegrid->tiles[object->tilePos.y][object->tilePos.x - 1].worldPos, tilegrid->tileSize))
                {
                    tilegrid->moveToTile(object, VectorMath2(object->tilePos.x - 1, object->tilePos.y));
                }
                else if(pointInsideTile(object->pos, tilegrid->tiles[object->tilePos.y + 1][object->tilePos.x].worldPos, tilegrid->tileSize))
                {
                    tilegrid->moveToTile(object, VectorMath2(object->tilePos.x - 1, object->tilePos.y + 1));
                }
                else // it's inside upper left
                {
                    tilegrid->moveToTile(object, VectorMath2(object->tilePos.x - 1, object->tilePos.y - 1));
                }
            }
            else
            {
                // move up
                tilegrid->moveToTile(object, VectorMath2(object->tilePos.x, object->tilePos.y + 1));
            }
        }
        else if(direction.y < 0)
        {
            // 5 left to check
            if(direction.x > 0)
            {
                // 3 to check (down right)
                if(pointInsideTile(object->pos, tilegrid->tiles[object->tilePos.y - 1][object->tilePos.x].worldPos, tilegrid->tileSize))
                {
                    tilegrid->moveToTile(object, VectorMath2(object->tilePos.x, object->tilePos.y - 1));
                }
                else if(pointInsideTile(object->pos, tilegrid->tiles[object->tilePos.y][object->tilePos.x + 1].worldPos, tilegrid->tileSize))
                {
                    tilegrid->moveToTile(object, VectorMath2(object->tilePos.x + 1, object->tilePos.y));
                }
                else // it's inside lower right
                {
                    tilegrid->moveToTile(object, VectorMath2(object->tilePos.x + 1, object->tilePos.y - 1));
                }
            }
            else if(direction.x < 0)
            {
                // 3 to check (down left)
                if(pointInsideTile(object->pos, tilegrid->tiles[object->tilePos.y][object->tilePos.x - 1].worldPos, tilegrid->tileSize))
                {
                    tilegrid->moveToTile(object, VectorMath2(object->tilePos.x - 1, object->tilePos.y));
                }
                else if(pointInsideTile(object->pos, tilegrid->tiles[object->tilePos.y - 1][object->tilePos.x].worldPos, tilegrid->tileSize))
                {
                    tilegrid->moveToTile(object, VectorMath2(object->tilePos.x, object->tilePos.y - 1));
                }
                else // it's inside lower left
                {
                    tilegrid->moveToTile(object, VectorMath2(object->tilePos.x - 1, object->tilePos.y - 1));
                }
            }
            else
            {
                // move down
                tilegrid->moveToTile(object, VectorMath2(object->tilePos.x, object->tilePos.y - 1));
            }
        }
        else
        {
            // 2 left to check
            if(direction.x > 0)
            {
                // move right
                tilegrid->moveToTile(object, VectorMath2(object->tilePos.x + 1, object->tilePos.y));
            }
            else if(direction.x < 0)
            {
                // move left
                tilegrid->moveToTile(object, VectorMath2(object->tilePos.x - 1, object->tilePos.y));
            }
        }
    }
}
bool CollisionHandler::pointInsideTile(VectorMath2 pointPos, VectorMath2 tilePos, float tileSize)
{
    // add all points necessary before doing the math/comparisons
    float bottomLeftX, bottomLeftY, topRightX, topRightY;
    bottomLeftX = tilePos.x - tileSize/2;
    bottomLeftY = tilePos.y - tileSize/2;
    topRightX = tilePos.x + tileSize/2;
    topRightY = tilePos.y + tileSize/2;

    if(pointPos.x >= bottomLeftX && pointPos.x <= topRightX && 
       pointPos.y >= bottomLeftY && pointPos.y <= topRightY)
    {
        return true;
    }

    return false;
}

// void CollisionHandler::checkRayAgainstEnemies(VectorMath2 start, VectorMath2 direction, Tilegrid* tilegrid)
// {
//     direction.Normalize();

//     // -------- check inside player tile first --------
//     GameObject* player;
//     for(int i = 0; i < tilegrid->playerTile->gameObjects.size(); i++)
//     {
//         if(tilegrid->playerTile->gameObjects[i]->objectType == ObjectType::PLAYER)
//         {
//             player = tilegrid->playerTile->gameObjects[i];
//             tilegrid->playerTile->gameObjects.erase(tilegrid->playerTile->gameObjects.begin() + i);
//         }
//     }
//     for(int i = 0; i < tilegrid->playerTile->gameObjects.size(); i++)
//     {
//         VectorMath2 pointInTile = start;
//         pointInTile = pointInTile - direction * tilegrid->playerTile->size;
//         while(pointInsideTile(pointInTile, tilegrid->playerTile->worldPos, tilegrid->playerTile->size))
//         {
//             if(pointInsideTile(pointInTile, tilegrid->playerTile->gameObjects[i]->pos, tilegrid->playerTile->gameObjects[i]->size))
//             {
//                 std::cout << "Raycast hit an enemy" << std::endl;
//                 tilegrid->playerTile->gameObjects.erase(tilegrid->playerTile->gameObjects.begin() + i);
//                 i--;
//                 if(tilegrid->playerTile->gameObjects.empty())
//                 {
//                     break;
//                 }
//             }
//             pointInTile = pointInTile + direction * (tilegrid->playerTile->gameObjects[i]->size / 3);
//         }
//     }
//     // --------

//     // -------- walk through the tiles until ray is inside a wall --------
//     Tile* nextTile = nextTileInDirection(tilegrid->playerTile, direction, &start, tilegrid);
//     // move outside of player tile
//     while(nextTile->pos == tilegrid->playerTile->pos)
//     {
//         nextTile = nextTileInDirection(tilegrid->playerTile, direction, &start, tilegrid);
//     }
//     // check the rest of the tiles in ray direction
//     while(true)
//     {
//         if(nextTile->type == Type::WALL)
//         {
//             std::cout << "Raycast hit a wall" << std::endl;
//             break;
//         }
//         // if enemy is inside, check if ray is inside the enemy
//         for(int i = 0; i < nextTile->gameObjects.size(); i++)
//         {
//             // have points be more frequent inside tile to see if ray hit enemy
//             VectorMath2 pointInTile = nextTile->worldPos;
//             pointInTile = pointInTile - direction * nextTile->size;
//             while(pointInsideTile(pointInTile, nextTile->worldPos, nextTile->size))
//             {
//                 if(pointInsideTile(pointInTile, nextTile->gameObjects[i]->pos, nextTile->gameObjects[i]->size))
//                 {
//                     std::cout << "Raycast hit an enemy" << std::endl;
//                     nextTile->gameObjects.erase(nextTile->gameObjects.begin() + i);
//                     i--;
//                     if(nextTile->gameObjects.empty())
//                     {
//                         for(int j = 0; j < tilesToUpdate.size(); j++)
//                         {
//                             if(tilesToUpdate[j]->pos == nextTile->pos)
//                             {
//                                 tilesToUpdate.erase(tilesToUpdate.begin() + j);
//                                 j--;
//                             }
//                         }
//                         break;
//                     }
//                 }
//                 pointInTile = pointInTile + direction * (nextTile->gameObjects[i]->size / 3);
//             }
            
//         }
//         nextTile = nextTileInDirection(nextTile, direction, &start, tilegrid);
//     }
//     // --------
//     tilegrid->playerTile->gameObjects.push_back(player);
// }