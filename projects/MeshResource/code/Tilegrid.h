#pragma once

#include "Tile.h"
#include <cstdlib>
#include <map>

class Tilegrid {
public:
    int numOfX, numOfY;
    float sizeX, sizeY;
    float tileSize;
    std::vector<std::vector<Tile>> tiles;
    // might not need tileInPos, could fix tiles so it can use size() - 2 and size() - 1 for the bottom and top y border positions
    // lookup is pretty slow. Is used in TestApp, CollisionHandler and Tilegrid.
    std::map<VectorMath2, Tile> tileInPos;
    Tile* playerTile;
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

    void Draw(MatrixMath viewMat);

    ~Tilegrid();
};