#pragma once

#include <vector>
#include "Tile.h"
#include "TestObject.h"

class CollisionHandler {
public:
    std::vector<Tile*> tilesToUpdate;

    void registerTile(Tile* tile);
    void removeTile(Tile* tile);
    void handleCollisions();
};