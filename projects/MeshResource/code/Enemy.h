#pragma once
#include "core/MatrixMath.h"
#include "render/GraphicsNode.h"
#include <memory>

#include "GameObject.h"

class Enemy : public GameObject
{
private:
    MatrixMath positionMatrix = Identity();
    MatrixMath rotationMatrix = Identity();

    GraphicsNode* enemyObject;

    float posX = 0;
    float posY = 0;

public:
    Enemy();
    ~Enemy();
    void SetupEnemy(std::shared_ptr<ShaderResource> shaders);
    void MoveEnemy();
    void setRenderPos();
    void DrawEnemy();
    void Destroy();
};