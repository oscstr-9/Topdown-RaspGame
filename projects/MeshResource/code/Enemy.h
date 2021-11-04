#pragma once
#include "core/MatrixMath.h"
#include "render/GraphicsNode.h"
#include "render/ShaderResource.h"
#include "GameObject.h"
#include "Tilegrid.h"
#include <memory>

class Enemy : public GameObject
{
private:
    MatrixMath positionMatrix = Identity();
    MatrixMath rotationMatrix = Identity();
    MatrixMath rotationCorrectionMatrix = RotateMatrix(M_PI, VectorMath3(0,0,1))  * RotateMatrix(M_PI/2, VectorMath3(0,-1,0));

    GraphicsNode* enemyObject;

    float movementSpeed = 1.4;
    float rotAngle;

    unsigned int waveNum = 0;

    float collisionDistance = 0.4;
public:
    Enemy();
    Enemy(std::shared_ptr<ShaderResource> shaders, std::shared_ptr<TextureResource> objTexture, std::shared_ptr<MeshResource> objMesh, VectorMath2 posIn);
    ~Enemy();
    void MoveToPoint(VectorMath2 posIn, float deltaTime, class CollisionHandler* collisionHandler, class Tilegrid* tilegrid);
    void PlayerColCheck(class Player *player);
    void DrawEnemy();
    void Destroy();
};