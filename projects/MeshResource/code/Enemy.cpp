#include "Enemy.h"
#include "render/MESHRESOURCE.h"
#include "render/ShaderResource.h"

Enemy::Enemy(std::shared_ptr<ShaderResource> shaders, VectorMath2 posIn){
    pos.posVar = posIn;
// Find object textures
    std::shared_ptr<TextureResource> objTexture = std::make_shared<TextureResource>("moon.png");
    // Load object textures
    objTexture->LoadFromFile();
    // Object meshes
    std::shared_ptr<MeshResource> objMesh = MeshResource::LoadObj("moon2");
    // Object transform
    positionMatrix = MatrixMath::TranslationMatrix(VectorMath3(pos.posVar,-6.8)) * ScalarMatrix(VectorMath3(0.001, 0.001, 0.001)) * rotationCorrectionMatrix;
    // Object graphicnodes
    enemyObject = new GraphicsNode(objMesh, objTexture, shaders, positionMatrix);
}

void Enemy::MoveToPoint(VectorMath2 posIn, float deltaTime){

    VectorMath2 direction = pos.posVar - posIn;
    direction.Normalize();

    pos.posVar = pos.posVar - (direction * movementSpeed * deltaTime);

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
    positionMatrix = MatrixMath::TranslationMatrix(VectorMath3(pos.posVar,-6.8)) * ScalarMatrix(VectorMath3(0.001, 0.001, 0.001)) * RotateMatrix(rotAngle,VectorMath3(0, 0, -1)) * rotationCorrectionMatrix;
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