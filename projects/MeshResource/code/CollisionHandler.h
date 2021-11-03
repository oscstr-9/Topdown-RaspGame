#pragma once

#include <vector>
#include "Tilegrid.h"
#include "GameObject.h"
#include <stdio.h>

class CollisionHandler {
public:
    //std::vector<Tile*> tilesToUpdate;
    bool hasHitEnemy = false;
    int hitEnemyID = -1;

    // objectPos is the new position the object will get if no collision occurs
    bool hasCollidedWithWall(Tilegrid* tilegrid, VectorMath2 objectPos, float objectRadius, VectorMath2 tilePos);
    bool AABBCollision(VectorMath2 pos1, float size1, VectorMath2 pos2, float size2);
    void updateTilePos(GameObject* object, Tilegrid* tilegrid);
    bool pointInsideTile(VectorMath2 pointPos, VectorMath2 tilePos, float tileSize);
    bool hasCollidedWithEnemy(GameObject* player, Tilegrid* tilegrid, float enemySize);
    bool circleSquareIntersection(VectorMath2 circlePos, float radius, VectorMath2 squarePos, float squareSize);
    bool checkRayAgainstEnemies(VectorMath2 start, VectorMath2 direction, Tilegrid* tilegrid, VectorMath2 playerTilePos);
    Tile* nextTileInDirection(Tile* currentTile, VectorMath2 direction, VectorMath2* rayStart, Tilegrid* tilegrid);
    bool lineCircleCollision(float radius, VectorMath2 lineStart, VectorMath2 lineEnd, VectorMath2 circleCenter);
};