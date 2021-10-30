#pragma once

#include <vector>
#include "Tilegrid.h"
#include "GameObject.h"
#include <stdio.h>

class CollisionHandler {
public:
    //std::vector<Tile*> tilesToUpdate;

    // objectPos is the new position the object will get if no collision occurs
    bool hasCollidedWithWall(Tilegrid* tilegrid, VectorMath2 objectPos, float objectSize, VectorMath2 tilePos);
    bool AABBCollision(VectorMath2 pos1, float size1, VectorMath2 pos2, float size2);
    void updateTilePos(GameObject* object, Tilegrid* tilegrid);
    bool pointInsideTile(VectorMath2 pointPos, VectorMath2 tilePos, float tileSize);
    // void checkRayAgainstEnemies(VectorMath2 start, VectorMath2 direction, Tilegrid* tilegrid);
};