#pragma once

// TODO: use for the list of enemies that currently are inside this tile
#include <vector>
#include "render/GraphicsNode.h"
//#include "GameObject.h"
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
    Pos pos;
    std::vector<Tile> neighborWalls;
    std::vector<Tile> neighborGround;
    std::vector<GameObject*> gameObjects;
};