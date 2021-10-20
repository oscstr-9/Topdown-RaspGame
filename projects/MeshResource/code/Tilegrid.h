#pragma once

#include "Tile.h"
#include <cstdlib>

class Tilegrid {
public:
    int width, height;
    std::vector<std::vector<Tile>> tiles;
    GraphicsNode groundTile;
    GraphicsNode wallTile;
    std::vector<GraphicsNode> wallTiles;
    float offset = 2;
    int zPlacement = 0;

    Tilegrid();
    Tilegrid(int width, int height);

    void createGrid();
    void createGraphics(std::shared_ptr<ShaderResource> shaders);
    // void placeTiles();

    void draw();

    ~Tilegrid();
};