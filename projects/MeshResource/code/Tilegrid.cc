#include "Tilegrid.h"
#include "RenderDebug.h"

Tilegrid::Tilegrid(int numOfX, int numOfY, float zPlacement, float tileSize)
{
    this->numOfX = numOfX;
    this->numOfY = numOfY;
    this->zPlacement = zPlacement;
    this->tileSize = tileSize;
    createGrid(tileSize);
}

void Tilegrid::createGrid(float tileSize)
{
    // -------- Tiles --------
    int random;
    int increment = 0;
    float posY = -((float)numOfY/2) * tileSize + tileSize / 2;

    for(int y = 0; y < numOfY; y++)
    {
        // create new empty row for storing tiles
        std::vector<Tile> tileRow;
        tiles.push_back(tileRow);
        float posX = -((float)numOfX/2) * tileSize + tileSize / 2;
        for(int x = 0; x < numOfX; x++)
        {
            // create new tile to add to this row of tiles
            Tile tile;
            tile.size = tileSize;
            tile.pos.x = x;
            tile.pos.y = y;
            tile.worldPos = VectorMath2(posX, posY);

            // make the tile ground or wall
            srand(time(0) + increment++);
            random = rand()%10;
            // higher number means higher chance of becoming wall
            if(random < 1 || // random
               x == 0 || x == numOfX - 1 || y == 0 || y == numOfY - 1) // border
            {
                tile.type = Type::WALL;
            }
            else
            {
                tile.type = Type::GROUND;
            }

            tiles[y].push_back(tile);

            posX += tileSize;
        }
        posY += tileSize;
    }
    // -------- Grid size --------
    sizeX = numOfX * tiles[0][0].size;
    sizeY = numOfY * tiles[0][0].size;
}

void Tilegrid::createGraphics(std::shared_ptr<ShaderResource> shaders)
{
    // // ground, just one square at the size of the width * height of this tilegrid
    // std::shared_ptr<TextureResource> texture = std::make_shared<TextureResource>("wall.png");
    // texture->LoadFromFile();
    // std::shared_ptr<MeshResource> mesh = MeshResource::LoadObj("square");
    // MatrixMath transform = MatrixMath::TranslationMatrix(VectorMath3(0, 0, zPlacement)) * ScalarMatrix(VectorMath3(sizeX / 2, sizeY / 2, 1));
    // groundTile = GraphicsNode(mesh, texture, shaders, transform);

    // -------- walls, one graphicsnode per wall --------
    std::shared_ptr<TextureResource> wallTexture = std::make_shared<TextureResource>("cubepic.png");
    wallTexture->LoadFromFile();
    std::shared_ptr<MeshResource> wallMesh = MeshResource::LoadObj("cube");

    float wallPosY = -((float)numOfY/2) * tiles[0][0].size + tiles[0][0].size / 2;
    for(int y = 0; y < numOfY; y++)
    {
        VectorMath2 pos;
        float wallPosX = -((float)numOfX/2) * tiles[0][0].size + tiles[0][0].size / 2;
        for(int x = 0; x < numOfX; x++)
        {
            pos.y = y;
            pos.x = x;
            if(tiles[pos.y][pos.x].type == Type::WALL)
            {
                // wallPosX and wallPosY sets transform to its respective position in grid
                MatrixMath transform = MatrixMath::TranslationMatrix(VectorMath3(wallPosX, wallPosY, zPlacement + 0.3)) * 
                    ScalarMatrix(VectorMath3(tiles[pos.y][pos.x].size / 2, tiles[pos.y][pos.x].size / 2, 1));
                wallTiles.push_back(GraphicsNode(wallMesh, wallTexture, shaders, transform));
            }
            wallPosX += tiles[pos.y][pos.x].size;
        }
        wallPosY += tiles[pos.y][pos.x].size;
    }
    // --------
}

void Tilegrid::moveToTile(GameObject* object, VectorMath2 tilePos)
{
    for(int i = 0; i < tiles[object->tilePos.y][object->tilePos.x].gameObjects.size(); i++)
    {
        if(object->ID == tiles[object->tilePos.y][object->tilePos.x].gameObjects[i]->ID)
        {
            tiles[object->tilePos.y][object->tilePos.x].gameObjects.erase(
                tiles[object->tilePos.y][object->tilePos.x].gameObjects.begin() + i);
            object->tilePos = tilePos;
            tiles[object->tilePos.y][object->tilePos.x].gameObjects.push_back(object);
        }
    }
}

void Tilegrid::Draw(MatrixMath viewMat)
{
    //groundTile.Draw();
    for(GraphicsNode tile : wallTiles)
    {
        VectorMath4 cullingPos = VectorMath4(tile.getTransform()[3][0], tile.getTransform()[3][1],tile.getTransform()[3][2],tile.getTransform()[3][3]);
        cullingPos = viewMat.VectorMultiplication(cullingPos);
        cullingPos.x /= cullingPos.w;
        cullingPos.y /= cullingPos.w;
        
        if(cullingPos.x < 1.2 && cullingPos.x > -1.2 && cullingPos.y < 1.1 && cullingPos.y > -1.2){
            tile.Draw();
        }
    }

    // Debugging
  
    // for (int y = 0; y < numOfY; y++)
    // {
    //     for (int x = 0; x < numOfX; x++)
    //     {
    //         VectorMath4 cullingPos = VectorMath4(tiles[y][x].worldPos.x, tiles[y][x].worldPos.y, -7, 1);
    //         cullingPos = viewMat.VectorMultiplication(cullingPos);
    //         cullingPos.x /= cullingPos.w;
    //         cullingPos.y /= cullingPos.w;

    //         if(cullingPos.x < 1.1 && cullingPos.x > -1.1 && cullingPos.y < 1 && cullingPos.y > -1.2){
    //             Debug::DrawSquare(0.6, VectorMath3(tiles[y][x].worldPos, -6.9), VectorMath4(0,1,0,1));
    //         }
    //         else
    //             Debug::DrawSquare(0.6, VectorMath3(tiles[y][x].worldPos, -6.9), VectorMath4(1,0,0,1));
    //     } 
    // }
}


Tilegrid::~Tilegrid()
{
}
