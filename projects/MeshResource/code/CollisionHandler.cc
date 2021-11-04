#include "CollisionHandler.h"

bool CollisionHandler::hasCollidedWithWall(Tilegrid* tilegrid, VectorMath2 objectPos, float objectRadius, VectorMath2 tilePos)
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
                if(circleSquareIntersection(objectPos, objectRadius, tilegrid->tiles[neighborTileY][neighborTileX].worldPos, tilegrid->tiles[neighborTileY][neighborTileX].size))
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
                    tilegrid->moveToTile(object, VectorMath2(object->tilePos.x, object->tilePos.y + 1));
                }
                else // it's inside upper left
                {
                    tilegrid->moveToTile(object, VectorMath2(object->tilePos.x - 1, object->tilePos.y + 1));
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
bool CollisionHandler::hasCollidedWithEnemy(GameObject* player, Tilegrid* tilegrid, float enemySize)
{
    float distance = player->size / 2 + enemySize / 2;
    // Check its own tile
    for(int i = 0; i < tilegrid->tiles[player->tilePos.y][player->tilePos.x].gameObjects.size(); i++)
    {
        if(tilegrid->tiles[player->tilePos.y][player->tilePos.x].gameObjects[i]->objectType == ObjectType::PLAYER)
        {
            tilegrid->tiles[player->tilePos.y][player->tilePos.x].gameObjects.erase(
                tilegrid->tiles[player->tilePos.y][player->tilePos.x].gameObjects.begin() + i);
            break;
        }
    }
    for(int i = 0; i < tilegrid->tiles[player->tilePos.y][player->tilePos.x].gameObjects.size(); i++)
    {
        if((tilegrid->tiles[player->tilePos.y][player->tilePos.x].gameObjects[i]->pos - player->pos).Length() < distance)
        {
            tilegrid->tiles[player->tilePos.y][player->tilePos.x].gameObjects.push_back(player);
            return true;
        }
    }
    tilegrid->tiles[player->tilePos.y][player->tilePos.x].gameObjects.push_back(player);
    // Check all 8 neighbors
    for(int neighborTileY = player->tilePos.y - 1; neighborTileY <= player->tilePos.y + 1; neighborTileY++)
    {
        for(int neighborTileX = player->tilePos.x - 1; neighborTileX <= player->tilePos.x + 1; neighborTileX++)
        {
            if(VectorMath2(neighborTileX, neighborTileY) == player->tilePos)
                continue;
            for(int i = 0; i < tilegrid->tiles[neighborTileY][neighborTileX].gameObjects.size(); i++)
            {
                if((tilegrid->tiles[neighborTileY][neighborTileX].gameObjects[i]->pos - player->pos).Length() < distance)
                {
                    return true;
                }
            }
        }
    }
    return false;
}
bool CollisionHandler::circleSquareIntersection(VectorMath2 circlePos, float radius, VectorMath2 squarePos, float squareSize)
{
    float edgeX = circlePos.x;
    float edgeY = circlePos.y;
    squarePos.x -= squareSize/2;
    squarePos.y -= squareSize/2;
    if(circlePos.x < squarePos.x) // left
    {
        edgeX = squarePos.x;
    }
    else if(circlePos.x > squarePos.x + squareSize) // right
    {
        edgeX = squarePos.x + squareSize;
    }
    if(circlePos.y < squarePos.y) // bottom
    {
        edgeY = squarePos.y;
    }
    else if(circlePos.y > squarePos.y + squareSize) // top
    {
        edgeY = squarePos.y + squareSize;
    }

    float distX = circlePos.x - edgeX;
    float distY = circlePos.y - edgeY;
    float distance = sqrt(distX*distX + distY*distY);

    if(distance <= radius)
    {
        return true;
    }
    return false;
}
bool CollisionHandler::checkRayAgainstEnemies(VectorMath2 start, VectorMath2 direction, Tilegrid* tilegrid, VectorMath2 playerTilePos)
{
    direction.Normalize();
    //float stepSize = 100;
    VectorMath2 playerPos = VectorMath2(start.x, start.y);

    // -------- check inside player tile first --------
    GameObject* player;
    for(int i = 0; i < tilegrid->tiles[playerTilePos.y][playerTilePos.x].gameObjects.size(); i++)
    {
        if(tilegrid->tiles[playerTilePos.y][playerTilePos.x].gameObjects[i]->objectType == ObjectType::PLAYER)
        {
            player = tilegrid->tiles[playerTilePos.y][playerTilePos.x].gameObjects[i];
            tilegrid->tiles[playerTilePos.y][playerTilePos.x].gameObjects.erase(tilegrid->tiles[playerTilePos.y][playerTilePos.x].gameObjects.begin() + i);
            break;
        }
    }
    for(int i = 0; i < tilegrid->tiles[playerTilePos.y][playerTilePos.x].gameObjects.size(); i++)
    {
        // VectorMath2 pointInTile = start;
        // pointInTile = pointInTile + direction * (tilegrid->tiles[playerPos.y][playerPos.x].size / stepSize);
        // while(pointInsideTile(pointInTile, tilegrid->tiles[playerPos.y][playerPos.x].worldPos, tilegrid->tiles[playerPos.y][playerPos.x].size))
        // {
            // TODO: line circle intersection
            if(lineCircleCollision(tilegrid->tiles[playerTilePos.y][playerTilePos.x].gameObjects[i]->radius, playerPos, direction, tilegrid->tiles[playerTilePos.y][playerTilePos.x].gameObjects[i]->pos))
            {
                std::cout << "Raycast hit an enemy" << std::endl;
                hasHitEnemy = true;
                hitEnemyID = tilegrid->tiles[playerTilePos.y][playerTilePos.x].gameObjects[i]->ID;
                tilegrid->tiles[playerTilePos.y][playerTilePos.x].gameObjects.erase(tilegrid->tiles[playerTilePos.y][playerTilePos.x].gameObjects.begin() + i);
                tilegrid->tiles[playerTilePos.y][playerTilePos.x].gameObjects.push_back(player);
                return true;
            }
            //pointInTile = pointInTile + direction * (tilegrid->tiles[playerPos.y][playerPos.x].gameObjects[i]->size / stepSize);
        // }
    }
    tilegrid->tiles[playerTilePos.y][playerTilePos.x].gameObjects.push_back(player);
    // --------

    // -------- walk through the tiles until ray is inside a wall --------
    Tile* nextTile = nextTileInDirection(&tilegrid->tiles[playerTilePos.y][playerTilePos.x], direction, &start, tilegrid);
    // move outside of player tile
    while(nextTile->pos == tilegrid->tiles[playerTilePos.y][playerTilePos.x].pos)
    {
        nextTile = nextTileInDirection(&tilegrid->tiles[playerTilePos.y][playerTilePos.x], direction, &start, tilegrid);
    }
    // check the rest of the tiles in ray direction
    while(true)
    {
        if(nextTile->type == Type::WALL)
        {
            std::cout << "Raycast hit a wall" << std::endl;
            return false;
        }
        // if enemy is inside, check if ray is inside the enemy
        for(int i = 0; i < nextTile->gameObjects.size(); i++)
        {
            // have points be more frequent inside tile to see if ray hit enemy
            //playerPos.PrintVector();
            if(lineCircleCollision(nextTile->gameObjects[i]->radius, playerPos, direction, nextTile->gameObjects[i]->pos))
            {
                std::cout << "Raycast hit an enemy" << std::endl;
                hasHitEnemy = true;
                hitEnemyID = nextTile->gameObjects[i]->ID;
                nextTile->gameObjects.erase(nextTile->gameObjects.begin() + i);
                return true;
            }
        }
        nextTile = nextTileInDirection(nextTile, direction, &start, tilegrid);
    }
    // --------

    return false;
}
Tile* CollisionHandler::nextTileInDirection(Tile* currentTile, VectorMath2 direction, VectorMath2* rayStart, Tilegrid* tilegrid)
{
    Tile* nextTile;
    VectorMath2 nextPoint;
    VectorMath2 nextTilePos = currentTile->pos;
    float tileSize = currentTile->size / 10;
    nextPoint = *rayStart;
    if(direction.x > 0)
    {
        // +=
        nextPoint.x += direction.x * tileSize;
        if(pointInsideTile(nextPoint, tilegrid->tiles[nextTilePos.y][nextTilePos.x + 1].worldPos, currentTile->size))
        {
            nextTilePos.x++;
        }
    }
    else
    {
        // -=
        nextPoint.x += direction.x * tileSize;
        if(pointInsideTile(nextPoint, tilegrid->tiles[nextTilePos.y][nextTilePos.x - 1].worldPos, currentTile->size))
        {
            nextTilePos.x--;
        }
    }
    if(direction.y > 0)
    {
        // +=
        nextPoint.y += direction.y * tileSize;
        if(pointInsideTile(nextPoint, tilegrid->tiles[nextTilePos.y + 1][nextTilePos.x].worldPos, currentTile->size))
        {
            nextTilePos.y++;
        }
    }
    else
    {
        // -=
        nextPoint.y += direction.y * tileSize;
        if(pointInsideTile(nextPoint, tilegrid->tiles[nextTilePos.y - 1][nextTilePos.x].worldPos, currentTile->size))
        {
            nextTilePos.y--;
        }
    }
    rayStart->x = nextPoint.x;
    rayStart->y = nextPoint.y;
    nextTile = &tilegrid->tiles[nextTilePos.y][nextTilePos.x];
    return nextTile;
}
bool CollisionHandler::lineCircleCollision(float radius, VectorMath2 lineStart, VectorMath2 direction, VectorMath2 circleCenter)
{
    direction.Normalize();
    VectorMath2 circleLineVector = circleCenter - lineStart;
    circleLineVector.Normalize();
    lineStart.PrintVector();
    circleCenter.PrintVector();
    std::cout << " " << std::endl;
    direction.PrintVector();
    circleLineVector.PrintVector();

    float v = acos(direction.DotProduct(circleLineVector));
    std::cout << "dot product: " << direction.DotProduct(circleLineVector) << std::endl;
    std::cout << "v: " << v << std::endl;

    circleLineVector = circleCenter - lineStart;
    float distance = sin(v) * circleLineVector.Length();
    std::cout << "sin(v): " << sin(v) << std::endl;
    std::cout << "distance: " << distance << std::endl;
    
    if(distance < radius)
    {
        return true;
    }

    return false;
    // a normalized vector always has length == 1... 
    //float cosV = direction.Length() / circleLineVector.Length();
    // TODO: fix cosV, get a some other way
    // we have two directions, should be able to get the angle out of those.
    // har med dot product att göra o:
    //float cosV;



    // if(cosV > 1 - 0.00000000000001 || cosV < 1 + 0.00000000000001) // v becomes zero (nan) when cosV is 1
    // {
    //     return true;
    // }
    // float v = acos(cosV);

    // få distance med riktiga längden


}
