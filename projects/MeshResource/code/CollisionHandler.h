#pragma once

#include <vector>
#include "Tilegrid.h"
#include "TestObject.h"
#include <stdio.h>

class CollisionHandler {
public:
    std::vector<Tile*> tilesToUpdate;

    void removeTile(Tile* tile);
    void handleCollisions();
    bool AABBCollision(Pos pos1, float size1, Pos pos2, float size2);
    bool pointInsideTile(Pos pointPos, Pos tilePos, float tileSize);
};