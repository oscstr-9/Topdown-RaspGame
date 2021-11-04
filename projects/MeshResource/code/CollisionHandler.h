#pragma once

#include <vector>
#include "Tilegrid.h"
#include "GameObject.h"
#include <stdio.h>

class CollisionHandler {
public:
    bool hasHitEnemy = false;
    int hitEnemyID = -1;

    // used before object's new pos is set
    // checks object against the eight neighbor tiles of tilePos
    bool hasCollidedWithWall(Tilegrid* tilegrid, VectorMath2 objectPos, float objectRadius, VectorMath2 tilePos);
    // used in hasCollidedWithWall
    // squarePos is the world position of the square's middle point
    bool circleSquareIntersection(VectorMath2 circlePos, float radius, VectorMath2 squarePos, float squareSize);
    // used after an object's move function is done
    // puts object in new tile if outside of its current tile
    void updateTilePos(GameObject* object, Tilegrid* tilegrid);
    // returns true if 2D point is inside tile
    // tilePos is the world position of the tile's middle point
    bool pointInsideTile(VectorMath2 pointPos, VectorMath2 tilePos, float tileSize);
    // circle vs circle collision
    // checks around player (its own tile + its 8 neighbors)
    bool hasCollidedWithEnemy(GameObject* player, Tilegrid* tilegrid, float enemyRadius);
    // should probably be called shoot instead, returns true if an enemy has been hit
    // hitEnemyID gets registered and hasHitEnemy becomes true when an enemy has been hit
    bool checkRayAgainstEnemies(VectorMath2 start, VectorMath2 direction, Tilegrid* tilegrid, VectorMath2 playerTilePos);
    // used in checkRayAgainstEnemies for when ray is traversing grid
    Tile* nextTileInDirection(Tile* currentTile, VectorMath2 direction, VectorMath2* rayStart, Tilegrid* tilegrid);
    // direction is the direction of the line, length of line is infinite
    bool lineCircleCollision(VectorMath2 lineStart, VectorMath2 direction, VectorMath2 circleCenter, float radius);
};