#include "CollisionHandler.h"
#include "RenderDebug.h"

bool CollisionHandler::hasCollidedWithWall(Tilegrid* tilegrid, VectorMath2 objectPos, float objectRadius, VectorMath2 tilePos)
{
    // from bottom row to top row
    for(int neighborTileY = tilePos.y - 1; neighborTileY <= tilePos.y + 1; neighborTileY++)
    {
        // from left column to right column
        for(int neighborTileX = tilePos.x - 1; neighborTileX <= tilePos.x + 1; neighborTileX++)
        {
            if(VectorMath2(neighborTileX, neighborTileY) == tilePos)
                continue; // skips collision check for the middle (tilePos)
            if(tilegrid->tiles[neighborTileY][neighborTileX].type == Type::WALL)
            {
                if(circleSquareIntersection(objectPos, objectRadius, tilegrid->tiles[neighborTileY][neighborTileX].worldPos, tilegrid->tiles[neighborTileY][neighborTileX].size))
                    return true;
            }
        }
    }
    return false;
}

bool CollisionHandler::circleSquareIntersection(VectorMath2 circlePos, float radius, VectorMath2 squarePos, float squareSize)
{
    float edgeX = circlePos.x;
    float edgeY = circlePos.y;
    // change squarePos to lower left corner of the square
    squarePos.x -= squareSize/2;
    squarePos.y -= squareSize/2;

    // check where circle point is compared to the edges of the square
    if(circlePos.x < squarePos.x) // left
        edgeX = squarePos.x;
    
    else if(circlePos.x > squarePos.x + squareSize) // right
        edgeX = squarePos.x + squareSize;

    if(circlePos.y < squarePos.y) // bottom
        edgeY = squarePos.y;

    else if(circlePos.y > squarePos.y + squareSize) // top
        edgeY = squarePos.y + squareSize;

    // calculate distance
    float distX = circlePos.x - edgeX;
    float distY = circlePos.y - edgeY;
    float distance = sqrt(distX*distX + distY*distY);

    if(distance <= radius)
        return true;

    return false;
}

void CollisionHandler::updateTilePos(GameObject* object, Tilegrid* tilegrid)
{
    // if not inside tile anymore, move object to the new tile
    if(!pointInsideTile(object->pos, tilegrid->tiles[object->tilePos.y][object->tilePos.x].worldPos, tilegrid->tileSize))
    {
        VectorMath2 direction = object->pos - tilegrid->tiles[object->tilePos.y][object->tilePos.x].worldPos;
        // check which tile to move to
        if(direction.y > 0)
        {
            // 5 left to check
            if(direction.x > 0)
            {
                // 3 to check (up right)
                if(pointInsideTile(object->pos, tilegrid->tiles[object->tilePos.y][object->tilePos.x + 1].worldPos, tilegrid->tileSize)) {
                    tilegrid->moveToTile(object, VectorMath2(object->tilePos.x + 1, object->tilePos.y));
                }
                else if(pointInsideTile(object->pos, tilegrid->tiles[object->tilePos.y + 1][object->tilePos.x].worldPos, tilegrid->tileSize)) {
                    tilegrid->moveToTile(object, VectorMath2(object->tilePos.x, object->tilePos.y + 1));
                }
                else { // it's inside upper right
                    tilegrid->moveToTile(object, VectorMath2(object->tilePos.x + 1, object->tilePos.y + 1));
                }
            }
            else if(direction.x < 0)
            {
                // 3 to check (up left)
                if(pointInsideTile(object->pos, tilegrid->tiles[object->tilePos.y][object->tilePos.x - 1].worldPos, tilegrid->tileSize)) {
                    tilegrid->moveToTile(object, VectorMath2(object->tilePos.x - 1, object->tilePos.y));
                }
                else if(pointInsideTile(object->pos, tilegrid->tiles[object->tilePos.y + 1][object->tilePos.x].worldPos, tilegrid->tileSize)) {
                    tilegrid->moveToTile(object, VectorMath2(object->tilePos.x, object->tilePos.y + 1));
                }
                else { // it's inside upper left
                    tilegrid->moveToTile(object, VectorMath2(object->tilePos.x - 1, object->tilePos.y + 1));
                }
            }
            else { // move up
                tilegrid->moveToTile(object, VectorMath2(object->tilePos.x, object->tilePos.y + 1));
            }
        }
        else if(direction.y < 0)
        {
            // 5 left to check
            if(direction.x > 0)
            {
                // 3 to check (down right)
                if(pointInsideTile(object->pos, tilegrid->tiles[object->tilePos.y - 1][object->tilePos.x].worldPos, tilegrid->tileSize)) {
                    tilegrid->moveToTile(object, VectorMath2(object->tilePos.x, object->tilePos.y - 1));
                }
                else if(pointInsideTile(object->pos, tilegrid->tiles[object->tilePos.y][object->tilePos.x + 1].worldPos, tilegrid->tileSize)) {
                    tilegrid->moveToTile(object, VectorMath2(object->tilePos.x + 1, object->tilePos.y));
                }
                else { // it's inside lower right
                    tilegrid->moveToTile(object, VectorMath2(object->tilePos.x + 1, object->tilePos.y - 1));
                }
            }
            else if(direction.x < 0)
            {
                // 3 to check (down left)
                if(pointInsideTile(object->pos, tilegrid->tiles[object->tilePos.y][object->tilePos.x - 1].worldPos, tilegrid->tileSize)) {
                    tilegrid->moveToTile(object, VectorMath2(object->tilePos.x - 1, object->tilePos.y));
                }
                else if(pointInsideTile(object->pos, tilegrid->tiles[object->tilePos.y - 1][object->tilePos.x].worldPos, tilegrid->tileSize)) {
                    tilegrid->moveToTile(object, VectorMath2(object->tilePos.x, object->tilePos.y - 1));
                }
                else { // it's inside lower left
                    tilegrid->moveToTile(object, VectorMath2(object->tilePos.x - 1, object->tilePos.y - 1));
                }
            }
            else {
                // move down
                tilegrid->moveToTile(object, VectorMath2(object->tilePos.x, object->tilePos.y - 1));
            }
        }
        else
        {
            // 2 left to check
            if(direction.x > 0) {
                // move right
                tilegrid->moveToTile(object, VectorMath2(object->tilePos.x + 1, object->tilePos.y));
            }
            else if(direction.x < 0) {
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

bool CollisionHandler::hasCollidedWithEnemy(GameObject* player, Tilegrid* tilegrid, float enemyRadius)
{
    // Remove player from its tile to avoid collision with itself
    for(int i = 0; i < tilegrid->tiles[player->tilePos.y][player->tilePos.x].gameObjects.size(); i++)
    {
        if(tilegrid->tiles[player->tilePos.y][player->tilePos.x].gameObjects[i]->objectType == ObjectType::PLAYER)
        {
            tilegrid->tiles[player->tilePos.y][player->tilePos.x].gameObjects.erase(
                tilegrid->tiles[player->tilePos.y][player->tilePos.x].gameObjects.begin() + i);
            break;
        }
    }

    // Check all 8 neighbors and its own tile
    float distance = player->radius + enemyRadius;
    for(int neighborTileY = player->tilePos.y - 1; neighborTileY <= player->tilePos.y + 1; neighborTileY++)
    {
        for(int neighborTileX = player->tilePos.x - 1; neighborTileX <= player->tilePos.x + 1; neighborTileX++)
        {
            for(int i = 0; i < tilegrid->tiles[neighborTileY][neighborTileX].gameObjects.size(); i++)
            {
                if((tilegrid->tiles[neighborTileY][neighborTileX].gameObjects[i]->pos - player->pos).Length() < distance)
                {
                    tilegrid->tiles[player->tilePos.y][player->tilePos.x].gameObjects.push_back(player);
                    return true;
                }
            }
        }
    }

    tilegrid->tiles[player->tilePos.y][player->tilePos.x].gameObjects.push_back(player);
    return false;
}

bool CollisionHandler::checkRayAgainstEnemies(VectorMath2 start, VectorMath2 direction, Tilegrid* tilegrid, VectorMath2 playerTilePos)
{
    direction.Normalize();
    VectorMath2 playerPos = VectorMath2(start.x, start.y);

    // -------- make it so player doesn't collide with itself --------
    // add player back to its tile before returning out of function
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
    // --------

    // -------- walk through the tiles until ray is inside a wall --------
    Tile* nextTile = nextTileInDirection(&tilegrid->tiles[playerTilePos.y][playerTilePos.x], direction, &start, tilegrid);
    while(true)
    {
        if(nextTile->type == Type::WALL) {
            // std::cout << "Raycast hit a wall" << std::endl;
            Debug::DrawLine(VectorMath3(player->pos, -7), VectorMath3(start, -6.5), VectorMath4(1,0.5,0,1));
            tilegrid->tiles[playerTilePos.y][playerTilePos.x].gameObjects.push_back(player);
            return false;
        }
        // if enemy is inside tile, check if ray is inside the enemy
        for(int i = 0; i < nextTile->gameObjects.size(); i++)
        {
            if(lineCircleCollision(playerPos, direction, nextTile->gameObjects[i]->pos, nextTile->gameObjects[i]->radius)) {
                // std::cout << "Raycast hit an enemy" << std::endl;
                Debug::DrawLine(VectorMath3(player->pos, -7), VectorMath3(start, -6.5), VectorMath4(1,0.5,0,1));
                hasHitEnemy = true;
                hitEnemyID = nextTile->gameObjects[i]->ID;
                nextTile->gameObjects.erase(nextTile->gameObjects.begin() + i);
                tilegrid->tiles[playerTilePos.y][playerTilePos.x].gameObjects.push_back(player);
                return true;
            }
        }
        nextTile = nextTileInDirection(nextTile, direction, &start, tilegrid);
    }
    // --------

    tilegrid->tiles[playerTilePos.y][playerTilePos.x].gameObjects.push_back(player);
    return false;
}

Tile* CollisionHandler::nextTileInDirection(Tile* currentTile, VectorMath2 direction, VectorMath2* rayStart, Tilegrid* tilegrid)
{
    VectorMath2 nextTilePos = currentTile->pos;
    float stepSize = currentTile->size / 10;

    // if inside new tile after stepping in direction, update nextTilePos
    if(direction.x > 0) { // +=
        rayStart->x += direction.x * stepSize;
        if(pointInsideTile(*rayStart, tilegrid->tiles[nextTilePos.y][nextTilePos.x + 1].worldPos, currentTile->size))
            nextTilePos.x++;
    }
    else { // -=
        rayStart->x += direction.x * stepSize;
        if(pointInsideTile(*rayStart, tilegrid->tiles[nextTilePos.y][nextTilePos.x - 1].worldPos, currentTile->size))
            nextTilePos.x--;
    }
    if(direction.y > 0) { // +=
        rayStart->y += direction.y * stepSize;
        if(pointInsideTile(*rayStart, tilegrid->tiles[nextTilePos.y + 1][nextTilePos.x].worldPos, currentTile->size))
            nextTilePos.y++;
    }
    else { // -=
        rayStart->y += direction.y * stepSize;
        if(pointInsideTile(*rayStart, tilegrid->tiles[nextTilePos.y - 1][nextTilePos.x].worldPos, currentTile->size))
            nextTilePos.y--;
    }
    return &tilegrid->tiles[nextTilePos.y][nextTilePos.x];
}

bool CollisionHandler::lineCircleCollision(VectorMath2 lineStart, VectorMath2 direction, VectorMath2 circleCenter, float radius)
{
    VectorMath2 circleLineVector = circleCenter - lineStart;
    direction.Normalize();
    circleLineVector.Normalize();
    float v = acos(direction.DotProduct(circleLineVector));

    circleLineVector = circleCenter - lineStart;
    float distance = sin(v) * circleLineVector.Length();
    
    if(distance < radius)
        return true;

    return false;
}
