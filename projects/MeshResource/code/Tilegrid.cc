#include "Tilegrid.h"

Tilegrid::Tilegrid(int numOfX, int numOfY, float zPlacement, float tileSize)
{
    this->numOfX = numOfX;
    this->numOfY = numOfY;
    this->zPlacement = zPlacement;
    createGrid(tileSize);
}

void Tilegrid::createGrid(float tileSize)
{
    // -------- Tiles --------
    int random;
    int increment = 0;
    for(int y = 0; y < numOfY; y++)
    {
        // create new empty row for storing tiles
        std::vector<Tile> tileRow;
        tiles.push_back(tileRow);
        for(int x = 0; x < numOfX; x++)
        {
            // create new tile to add to this row of tiles
            Tile tile;
            tile.size = tileSize;
            tile.pos.posVar.x = x;
            tile.pos.posVar.y = y;

            // make the tile ground or wall
            srand(time(0) + increment++);
            random = rand()%10;
            // lower number means less chance of becoming ground
            if(random < 9)
            {
                tile.type = Type::GROUND;
            }
            else
            {
                tile.type = Type::WALL;
            }

            tiles[y].push_back(tile);
            tileInPos.insert(std::make_pair(tile.pos, tile));
        }
    }
    // -------- Add walls around grid --------
    for(int y = -1; y < numOfY + 1; y++)
    {
        // create new empty row for storing tiles
        std::vector<Tile> tileRow;
        tiles.push_back(tileRow);
        // bottom and top border
        if(y == -1 || y == numOfY)
        {
            for(int x = -1; x < numOfX + 1; x++)
            {
                // create new tile to add to this row of tiles
                Tile tile;
                tile.size = tileSize;
                tile.pos.posVar.x = x;
                tile.pos.posVar.y = y;
                tile.type = Type::WALL;
                tiles[tiles.size() - 1].push_back(tile);
                tileInPos.insert(std::make_pair(tile.pos, tile));
            }
        }
        // side borders
        else
        {
            Tile tile;
            tile.size = tileSize;
            tile.pos.posVar.x = -1;
            tile.pos.posVar.y = y;
            tile.type = Type::WALL;
            tiles[tiles.size() - 1].push_back(tile);
            tileInPos.insert(std::make_pair(tile.pos, tile));

            tile.size = tileSize;
            tile.pos.posVar.x = numOfX;
            tiles[tiles.size() - 1].push_back(tile);
            tileInPos.insert(std::make_pair(tile.pos, tile));
        }
    }
    // -------- Grid size --------
    Pos pos;
    pos.posVar.x = 0;
    pos.posVar.y = 0;
    sizeX = numOfX * tileInPos.at(pos).size;
    sizeY = numOfY * tileInPos.at(pos).size;
    // -------- Add neighbors to the tiles --------
    for(int y = 0; y < numOfY; y++)
    {
        for(int x = 0; x < numOfX; x++)
        {
            pos.posVar.y = y;
            pos.posVar.x = x;
            if(tileInPos.at(pos).type == Type::WALL)
            {
                addWallToNeighbors(tiles[y][x]);
            }
            else
            {
                addGroundToNeighbors(tiles[y][x]);
            }
        }
    }
}

void Tilegrid::addWallToNeighbors(Tile wall)
{
    Pos upLeftPos, upPos, upRightPos, leftPos, rightPos, downLeftPos, downPos, downRightPos;
    upLeftPos.posVar.x = wall.pos.posVar.x - 1;
    upLeftPos.posVar.y = wall.pos.posVar.y + 1;
    upPos.posVar.x = wall.pos.posVar.x;
    upPos.posVar.y = wall.pos.posVar.y + 1;
    upRightPos.posVar.x = wall.pos.posVar.x + 1;
    upRightPos.posVar.y = wall.pos.posVar.y + 1;
    leftPos.posVar.x = wall.pos.posVar.x - 1;
    leftPos.posVar.y = wall.pos.posVar.y;
    rightPos.posVar.x = wall.pos.posVar.x + 1;
    rightPos.posVar.y = wall.pos.posVar.y;
    downLeftPos.posVar.x = wall.pos.posVar.x - 1;
    downLeftPos.posVar.y = wall.pos.posVar.y - 1;
    downPos.posVar.x = wall.pos.posVar.x;
    downPos.posVar.y = wall.pos.posVar.y - 1;
    downRightPos.posVar.x = wall.pos.posVar.x + 1;
    downRightPos.posVar.y = wall.pos.posVar.y - 1;

    // check if pos is on a tile before adding
    if(upLeftPos.posVar.x != -2 && upLeftPos.posVar.y != numOfY + 1)
        tileInPos.at(upLeftPos).neighborWalls.push_back(wall);
    if(upPos.posVar.y != numOfY + 1)
        tileInPos.at(upPos).neighborWalls.push_back(wall);
    if(upRightPos.posVar.x != numOfX + 1 && upRightPos.posVar.y != numOfY + 1)
        tileInPos.at(upRightPos).neighborWalls.push_back(wall);
    if(leftPos.posVar.x != -2)
        tileInPos.at(leftPos).neighborWalls.push_back(wall);
    if(rightPos.posVar.x != numOfX + 1)
        tileInPos.at(rightPos).neighborWalls.push_back(wall);
    if(downLeftPos.posVar.x != -2 && downLeftPos.posVar.y != -2)
        tileInPos.at(downLeftPos).neighborWalls.push_back(wall);
    if(downPos.posVar.y != -2)
        tileInPos.at(downPos).neighborWalls.push_back(wall);
    if(downRightPos.posVar.x != numOfX + 1 && downRightPos.posVar.y != -2)
        tileInPos.at(downRightPos).neighborWalls.push_back(wall);

}
void Tilegrid::addGroundToNeighbors(Tile ground)
{
    Pos upLeftPos, upPos, upRightPos, leftPos, rightPos, downLeftPos, downPos, downRightPos;
    upLeftPos.posVar.x = ground.pos.posVar.x - 1;
    upLeftPos.posVar.y = ground.pos.posVar.y + 1;
    upPos.posVar.x = ground.pos.posVar.x;
    upPos.posVar.y = ground.pos.posVar.y + 1;
    upRightPos.posVar.x = ground.pos.posVar.x + 1;
    upRightPos.posVar.y = ground.pos.posVar.y + 1;
    leftPos.posVar.x = ground.pos.posVar.x - 1;
    leftPos.posVar.y = ground.pos.posVar.y;
    rightPos.posVar.x = ground.pos.posVar.x + 1;
    rightPos.posVar.y = ground.pos.posVar.y;
    downLeftPos.posVar.x = ground.pos.posVar.x - 1;
    downLeftPos.posVar.y = ground.pos.posVar.y - 1;
    downPos.posVar.x = ground.pos.posVar.x;
    downPos.posVar.y = ground.pos.posVar.y - 1;
    downRightPos.posVar.x = ground.pos.posVar.x + 1;
    downRightPos.posVar.y = ground.pos.posVar.y - 1;

    // check if pos is on a tile before adding
    if(upLeftPos.posVar.x != -2 && upLeftPos.posVar.y != numOfY + 1)
        tileInPos.at(upLeftPos).neighborGround.push_back(ground);
    if(upPos.posVar.y != numOfY + 1)
        tileInPos.at(upPos).neighborGround.push_back(ground);
    if(upRightPos.posVar.x != numOfX + 1 && upRightPos.posVar.y != numOfY + 1)
        tileInPos.at(upRightPos).neighborGround.push_back(ground);
    if(leftPos.posVar.x != -2)
        tileInPos.at(leftPos).neighborGround.push_back(ground);
    if(rightPos.posVar.x != numOfX + 1)
        tileInPos.at(rightPos).neighborGround.push_back(ground);
    if(downLeftPos.posVar.x != -2 && downLeftPos.posVar.y != -2)
        tileInPos.at(downLeftPos).neighborGround.push_back(ground);
    if(downPos.posVar.y != -2)
        tileInPos.at(downPos).neighborGround.push_back(ground);
    if(downRightPos.posVar.x != numOfX + 1 && downRightPos.posVar.y != -2)
        tileInPos.at(downRightPos).neighborGround.push_back(ground);

}

// setup everything so only draw needs to be called during runtime
// assumes the square and wall are the same size; from -1 to 1 in the obj file
void Tilegrid::createGraphics(std::shared_ptr<ShaderResource> shaders, bool showBorders)
{
    // ground, just one square at the size of the width * height of this tilegrid
    std::shared_ptr<TextureResource> texture = std::make_shared<TextureResource>("wall.png");
    texture->LoadFromFile();
    std::shared_ptr<MeshResource> mesh = MeshResource::LoadObj("square");
    MatrixMath transform = MatrixMath::TranslationMatrix(VectorMath3(0, 0, zPlacement)) * ScalarMatrix(VectorMath3(sizeX, sizeY, 1));
    groundTile = GraphicsNode(mesh, texture, shaders, transform);

    // walls, one graphicsnode per wall
    std::shared_ptr<TextureResource> wallTexture = std::make_shared<TextureResource>("cubepic.png");
    wallTexture->LoadFromFile();
    std::shared_ptr<MeshResource> wallMesh = MeshResource::LoadObj("cube");
    for(int y = 0; y < numOfY; y++)
    {
        for(int x = 0; x < numOfX; x++)
        {
            Pos pos;
            pos.posVar.y = y;
            pos.posVar.x = x;
            if(tileInPos.at(pos).type == Type::WALL)
            {
                MatrixMath transform = Identity(); // wall transform is set in placeWalls()
                wallTiles.push_back(GraphicsNode(wallMesh, wallTexture, shaders, transform));
            }
        }
    }

    // set the rendering of each wall to be in their respective spot on the grid
    placeWalls();
    if(showBorders)
        createBorderGraphics(shaders);
}

void Tilegrid::createBorderGraphics(std::shared_ptr<ShaderResource> shaders)
{
    std::shared_ptr<TextureResource> texture = std::make_shared<TextureResource>("cubepic.png");
    texture->LoadFromFile();
    std::shared_ptr<MeshResource> mesh = MeshResource::LoadObj("cube");

    Pos pos;
    pos.posVar.x = 0;
    pos.posVar.y = 0;
    float wallPosX = -(numOfX + 1) * tileInPos.at(pos).size;
    float wallPosY = -(numOfY + 1) * tileInPos.at(pos).size;

    float zOffset = 0.8;

    for(int y = -1; y < numOfY + 1; y++)
    {
        wallPosX = -(numOfX + 1) * tileInPos.at(pos).size;
        // bottom and top border
        if(y == -1 || y == numOfY)
        {
            for(int x = -1; x < numOfX + 1; x++)
            {
                MatrixMath transform = MatrixMath::TranslationMatrix(VectorMath3(wallPosX, wallPosY, zPlacement + zOffset)) * 
                    ScalarMatrix(VectorMath3(tileInPos.at(pos).size, tileInPos.at(pos).size, 1));
                wallTiles.push_back(GraphicsNode(mesh, texture, shaders, transform));
                wallPosX += 2 * tileInPos.at(pos).size;
            }
            wallPosY += 2 * tileInPos.at(pos).size;
        }
        // side borders
        else
        {
            // left
            MatrixMath transform = MatrixMath::TranslationMatrix(VectorMath3(wallPosX, wallPosY, zPlacement + zOffset)) * 
                    ScalarMatrix(VectorMath3(tileInPos.at(pos).size, tileInPos.at(pos).size, 1));
            wallTiles.push_back(GraphicsNode(mesh, texture, shaders, transform));
            wallPosX += 2 * tileInPos.at(pos).size * (numOfX + 1);

            // right
            transform = MatrixMath::TranslationMatrix(VectorMath3(wallPosX, wallPosY, zPlacement + zOffset)) * 
                    ScalarMatrix(VectorMath3(tileInPos.at(pos).size, tileInPos.at(pos).size, 1));
            wallTiles.push_back(GraphicsNode(mesh, texture, shaders, transform));
            wallPosY += 2 * tileInPos.at(pos).size;
        }
    }
}

void Tilegrid::placeWalls()
{
    Pos pos;
    pos.posVar.x = 0;
    pos.posVar.y = 0;
    float wallPosX = -(numOfX - 1) * tileInPos.at(pos).size;
    float wallPosY = -(numOfY - 1) * tileInPos.at(pos).size;
    int wallInt = 0;
    for(int y = 0; y < numOfY; y++)
    {
        wallPosX = -(numOfX - 1) * tileInPos.at(pos).size;
        for(int x = 0; x < numOfX; x++)
        {
            pos.posVar.y = y;
            pos.posVar.x = x;
            if(tileInPos.at(pos).type == Type::WALL)
            {
                MatrixMath transform = MatrixMath::TranslationMatrix(VectorMath3(wallPosX, wallPosY, zPlacement + 0.3)) * 
                    ScalarMatrix(VectorMath3(tileInPos.at(pos).size, tileInPos.at(pos).size, 1));
                wallTiles[wallInt++].setTransform(transform);
            }
            wallPosX += 2 * tileInPos.at(pos).size;
        }
        wallPosY += 2 * tileInPos.at(pos).size;
    }
}

void Tilegrid::Draw()
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