#pragma once

#include "Tile.h"
#include <cstdlib>
#include <map>

class Tilegrid {
public:
    int numOfX, numOfY;
    float sizeX, sizeY;
    std::vector<std::vector<Tile>> tiles;
    std::map<Pos, Tile> tileInPos;
    // Placement of {x, y} in grid:
    // {0, 2} {1, 2} {2, 2}
    // {0, 1} {1, 1} {2, 1}
    // {0, 0} {0, 1} {2, 0}
    GraphicsNode groundTile;
    std::vector<GraphicsNode> wallTiles;
    float zPlacement;

    Tilegrid(int numOfX, int numOfY, float zPlacement, float tileSize);

    void createGrid(float tileSize);
    void createGraphics(std::shared_ptr<ShaderResource> shaders, bool showBorders);
    void createBorderGraphics(std::shared_ptr<ShaderResource> shaders);
    void placeWalls();
    void addWallToNeighbors(Tile wall);
    void addGroundToNeighbors(Tile ground);

    void Draw();

    ~Tilegrid();
};