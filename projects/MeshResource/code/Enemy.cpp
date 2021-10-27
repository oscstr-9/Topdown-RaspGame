#include "Enemy.h"
#include "render/MESHRESOURCE.h"
#include "RenderDebug.h"
#include <vector>
#include <stdlib.h>

Enemy::Enemy(){
}

Enemy::Enemy(std::shared_ptr<ShaderResource> shaders, VectorMath2 posIn){
    pos = posIn;
// Find object textures
    std::shared_ptr<TextureResource> objTexture = std::make_shared<TextureResource>("moon.png");
    // Load object textures
    objTexture->LoadFromFile();
    // Object meshes
    std::shared_ptr<MeshResource> objMesh = MeshResource::LoadObj("moon2");
    // Object transform
    positionMatrix = MatrixMath::TranslationMatrix(VectorMath3(pos,-6.8)) * ScalarMatrix(VectorMath3(0.001, 0.001, 0.001)) * rotationCorrectionMatrix;
    // Object graphicnodes
    enemyObject = new GraphicsNode(objMesh, objTexture, shaders, positionMatrix);
}

void Enemy::MoveToPoint(VectorMath2 posIn, float deltaTime){

    VectorMath2 direction = pos - posIn;
    direction.Normalize();

    previousPos = pos;
    pos = pos - (direction * movementSpeed * deltaTime);

    if (direction.x != 0){
        rotAngle = -atan(direction.y / direction.x)+M_PI/2;
        if(direction.x < 0){
            rotAngle += M_PI;
        }
    }
    else{
        if(direction. y<0)
            rotAngle = M_PI;
        else if(direction.y>0)
            rotAngle = 0;
    }
    positionMatrix = MatrixMath::TranslationMatrix(VectorMath3(pos,-6.8)) * ScalarMatrix(VectorMath3(0.001, 0.001, 0.001)) * RotateMatrix(rotAngle,VectorMath3(0, 0, -1)) * rotationCorrectionMatrix;
    enemyObject->setTransform(positionMatrix);
}

void Enemy::CreateSpawnWave(std::shared_ptr<ShaderResource> shader, MatrixMath viewMat, Tilegrid tilegrid){
    std::vector<Enemy> enemies;
    std::vector<VectorMath2> freeSpawnLoactions;


    for (int x = 0; x < tilegrid.numOfX; x++)
    {
        for (int y = 0; y < tilegrid.numOfY; y++)
            {
                VectorMath4 cullingPos = VectorMath4(tilegrid.tiles[y][x].worldPos.x, tilegrid.tiles[y][x].worldPos.y, -7, 1);
                cullingPos = viewMat.VectorMultiplication(cullingPos);
                cullingPos.x /= cullingPos.w;
                cullingPos.y /= cullingPos.w;

                if(cullingPos.x < 1.1 && cullingPos.x > -1.1 && cullingPos.y < 1 && cullingPos.y > -1.2){
                    freeSpawnLoactions.push_back(VectorMath2(tilegrid.tiles[y][x].worldPos.x, tilegrid.tiles[y][x].worldPos.y));
                }
            }
        }
    
    for (int i = 0; i < 10 + pow(waveNum,2); i++)
    {
        //Enemy enemy = Enemy(shader, freeSpawnLoactions[rand() % freeSpawnLoactions.size()]);
        //enemies.push_back(enemy);
        Debug::DrawSquare(0.6, VectorMath3(freeSpawnLoactions[rand() % (freeSpawnLoactions.size()-1)], -6.5), VectorMath4(0,0,1,1));
    }

    waveNum++;
    
}

void Enemy::DrawEnemy(){
    enemyObject->Draw();
}

void Enemy::Destroy(){
    // destroy enemy
}

Enemy::~Enemy(){
    Destroy();
}