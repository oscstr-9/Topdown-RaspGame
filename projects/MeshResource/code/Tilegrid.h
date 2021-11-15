#pragma once

#include "Tile.h"
#include <cstdlib>
#include <map>

class Tilegrid {
public:
    int numOfX, numOfY;
    float sizeX, sizeY;
    float tileSize;
    // Placement of {x, y} in grid:
    // {0, 2} {1, 2} {2, 2}
    // {0, 1} {1, 1} {2, 1}
    // {0, 0} {0, 1} {2, 0}
    std::vector<std::vector<Tile>> tiles;
    GraphicsNode groundTile;
    std::vector<GraphicsNode> wallTiles;
    float zPlacement;

    Tilegrid(int numOfX, int numOfY, float zPlacement, float tileSize);

    void createGrid(float tileSize);
    // setup everything so only draw needs to be called during runtime
    // assumes the square and wall are the same size; from -1 to 1 in the obj file
    void createGraphics(std::shared_ptr<ShaderResource> shaders);
    // removes object from its old tile and adds it to the new tile in tilePos
    void moveToTile(GameObject* object, VectorMath2 tilePos);
    // playerPos makes sure no walls spawn near player
    void reset(Player* player, std::shared_ptr<ShaderResource> shaders);

    void Draw(MatrixMath viewMat);

    ~Tilegrid();
};