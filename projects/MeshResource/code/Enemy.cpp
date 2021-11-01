#include "Enemy.h"
#include "render/MESHRESOURCE.h"
#include "RenderDebug.h"
#include <vector>
#include <stdlib.h>
#include "CollisionHandler.h"
#include "Tilegrid.h"

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

void Enemy::MoveToPoint(VectorMath2 posIn, float deltaTime, CollisionHandler* collisionHandler, Tilegrid* tilegrid){

    VectorMath2 direction = pos - posIn;
    direction.Normalize();

    if(!collisionHandler->hasCollidedWithWall(tilegrid, VectorMath2(pos.x, pos.y - direction.y * movementSpeed * deltaTime), size, tilePos))
    {
        pos.y -= direction.y * movementSpeed * deltaTime;
    }
    if(!collisionHandler->hasCollidedWithWall(tilegrid, VectorMath2(pos.x - direction.x * movementSpeed * deltaTime, pos.y), size, tilePos))
    {
        pos.x -= direction.x * movementSpeed * deltaTime;
    }

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

void Enemy::DrawEnemy(){
    enemyObject->Draw();
}

void Enemy::Destroy(){
    // destroy enemy
}

Enemy::~Enemy(){
    Destroy();
}