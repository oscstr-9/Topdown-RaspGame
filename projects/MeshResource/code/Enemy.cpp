#include "Enemy.h"
#include "render/MESHRESOURCE.h"
#include "render/ShaderResource.h"

Enemy::Enemy(){
    // Cool Cool
}
void Enemy::SetupEnemy(std::shared_ptr<ShaderResource> shaders){
    // Find object textures
    std::shared_ptr<TextureResource> objTexture = std::make_shared<TextureResource>("moon.png");
    // Load object textures
    objTexture->LoadFromFile();
    // Object meshes
    std::shared_ptr<MeshResource> objMesh = MeshResource::LoadObj("moon2");
    // Object transform
    MatrixMath rotationCorrectionMatrix = RotateMatrix(M_PI, VectorMath3(0,0,1))  * RotateMatrix(M_PI/2, VectorMath3(0,-1,0));
    positionMatrix = MatrixMath::TranslationMatrix(VectorMath3(posX, posY,-6.8)) * ScalarMatrix(VectorMath3(0.001, 0.001, 0.001)) * rotationCorrectionMatrix;
    // Object graphicnodes
    enemyObject = new GraphicsNode(objMesh, objTexture, shaders, positionMatrix);
}

void Enemy::setRenderPos()
{
    posX = pos.x;
    posY = pos.y;
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