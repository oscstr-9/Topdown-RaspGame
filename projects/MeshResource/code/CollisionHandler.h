#pragma once

#include <vector>
#include "Tilegrid.h"
#include "GameObject.h"
#include <stdio.h>

class CollisionHandler {
public:
    std::vector<Tile*> tilesToUpdate;

    void removeTile(Tile* tile);
    void handleCollisions(Tilegrid* tilegrid);
    bool AABBCollision(VectorMath2 pos1, float size1, VectorMath2 pos2, float size2);
    bool pointInsideTile(VectorMath2 pointPos, VectorMath2 tilePos, float tileSize);
    bool updateListOfTiles(Tile* tile, Tilegrid* tilegrid);
    void moveObjectsToNeighborOfTile(Tile* tile, Tilegrid* tilegrid);
};