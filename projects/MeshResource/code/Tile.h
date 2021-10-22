#pragma once

// TODO: use for the list of enemies that currently are inside this tile
#include <vector>
#include "render/GraphicsNode.h"

enum class Type
{
    GROUND,
    WALL
};

struct Pos
{
    int x, y;

    bool operator<(const Pos& pos) const {
        if(x < pos.x) return true;
        if(x > pos.x) return false;
        //x == coord.x
        if(y < pos.y) return true;
        if(y > pos.y) return false;

        return false;
    }
};

class Tile {
public:
    float size;
    Type type;
    Pos pos;
    std::vector<Tile> neighborWalls;

    Tile();

    ~Tile();
};