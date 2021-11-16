#include "Enemy.h"
#include "render/MESHRESOURCE.h"
#include "RenderDebug.h"
#include <vector>
#include <stdlib.h>
#include "CollisionHandler.h"
#include "Tilegrid.h"

Enemy::Enemy(){
}

Enemy::Enemy(std::shared_ptr<ShaderResource> shaders, std::shared_ptr<TextureResource> objTexture, std::shared_ptr<MeshResource> objMesh, VectorMath2 posIn){
    pos = posIn;
    // Object transform
    positionMatrix = MatrixMath::TranslationMatrix(VectorMath3(pos,-6.8)) * ScalarMatrix(VectorMath3(0.001, 0.001, 0.001)) * rotationCorrectionMatrix;
    // Object graphicnodes
    enemyObject = new GraphicsNode(objMesh, objTexture, shaders, positionMatrix);
}

void Enemy::MoveToPoint(VectorMath2 posIn, float deltaTime, CollisionHandler* collisionHandler, Tilegrid* tilegrid){

    VectorMath2 direction = pos - posIn;
    direction.Normalize();

    if(!collisionHandler->hasCollidedWithWall(tilegrid, VectorMath2(pos.x, pos.y - direction.y * movementSpeed * deltaTime), radius, tilePos))
    {
        pos.y -= direction.y * movementSpeed * deltaTime;
    }
    if(!collisionHandler->hasCollidedWithWall(tilegrid, VectorMath2(pos.x - direction.x * movementSpeed * deltaTime, pos.y), radius, tilePos))
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

void Enemy::PlayerColCheck(Player *player){
        if((pos - player->pos).Length() <= collisionDistance){
            player->Dead();
        }
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