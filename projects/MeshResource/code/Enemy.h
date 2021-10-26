#pragma once
#include "core/MatrixMath.h"
#include "render/GraphicsNode.h"
#include <memory>

class Enemy
{
private:
    MatrixMath positionMatrix = Identity();
    MatrixMath rotationMatrix = Identity();

    GraphicsNode* enemyObject;
public:
    Enemy();
    ~Enemy();
    void SetupEnemy(std::shared_ptr<ShaderResource> shaders);
    void MoveEnemy();
    void DrawEnemy();
    void Destroy();
};