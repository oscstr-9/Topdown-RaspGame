#pragma once

#include <vector>
#include "render/GraphicsNode.h"
#include "Player.h"

enum class Type
{
    GROUND,
    WALL
};

class Tile {
public:
    float size;
    Type type;
    // position in tilegrid
    VectorMath2 pos;
    // middle point of tile
    VectorMath2 worldPos;
    // can contain both enemies and the player
    std::vector<GameObject*> gameObjects;
};