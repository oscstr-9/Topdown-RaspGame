#include "Tilegrid.h"

Tilegrid::Tilegrid()
{
}
Tilegrid::Tilegrid(int height, int width)
{
    this->width = width;
    this->height = height;
    createGrid();
}

void Tilegrid::createGrid()
{
    int random;
    int increment = 0;
    for(int y = 0; y < height; y++)
    {
        // create new empty row for storing tiles
        std::vector<Tile> tileRow;
        tiles.push_back(tileRow);
        for(int x = 0; x < width; x++)
        {
            // create new tile to add to this row of tiles
            Tile tile;
            tile.pos.x = x;
            tile.pos.y = y;

            // generate ground or wall
            srand(time(0) + increment++);
            random = rand()%10;
            // replace 5 with 9 when less walls are desired
            if(random < 5)
            {
                tile.type = Type::GROUND;
            }
            else
            {
                tile.type = Type::WALL;
            }

            tiles[y].push_back(tile);
        }
    }
}


// setup everything so only draw needs to be called during runtime
void Tilegrid::createGraphics(std::shared_ptr<ShaderResource> shaders)
{
    // ground, just one square at the size of the width * height of this tilegrid
    // TODO: get ground.png and square.obj
    std::shared_ptr<TextureResource> texture = std::make_shared<TextureResource>("moon.png");
    texture->LoadFromFile();
    std::shared_ptr<MeshResource> mesh = MeshResource::LoadObj("moon2");
    // TODO: sync this graphic transform with the size of the grid
    MatrixMath transform = MatrixMath::TranslationMatrix(VectorMath3(1, 0, 0)) * ScalarMatrix(VectorMath3(0.005, 0.005, 0.005));
    groundTile = GraphicsNode(mesh, texture, shaders, transform);

    // walls, one graphicsnode per wall
    int offset = 0;
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            if(tiles[y][x].type == Type::WALL)
            {
                // TODO: get image and obj that represents a wall
                std::shared_ptr<TextureResource> texture = std::make_shared<TextureResource>("moon.png");
                texture->LoadFromFile();
                std::shared_ptr<MeshResource> mesh = MeshResource::LoadObj("moon2");
                // TODO: sync this graphic transform with the size of the grid
                MatrixMath transform = MatrixMath::TranslationMatrix(VectorMath3(offset++, 2, 0)) * ScalarMatrix(VectorMath3(0.005, 0.005, 0.005));
                wallTile = GraphicsNode(mesh, texture, shaders, transform);
                wallTiles.push_back(wallTile);
            }
        }
    }
}

void Tilegrid::draw()
{
    groundTile.Draw();
    for(GraphicsNode tile : wallTiles)
    {
        tile.Draw();
    }
}


Tilegrid::~Tilegrid()
{
}