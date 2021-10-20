#pragma once

// TODO: use for the list of enemies that currently are inside this tile
#include <vector>
// TODO: include Oscar's graphicsNode instead
#include "render/GraphicsNode.h"

enum class Type
{
    GROUND,
    WALL
};

struct Pos
{
    int x, y;
};

class Tile {
public:
    float size;
    Type type;
    // TODO: byt ut denna graphicsNode till Oscars graphicsNode
    Pos pos;

    Tile();
    Tile(float size, Type type);

    ~Tile();
};