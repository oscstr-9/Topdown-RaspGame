#pragma once
#include "core/VectorMath.h"
#include "core/MatrixMath.h"
#include "render/GraphicsNode.h"
#include "GameObject.h"
#include "UI.h"
#include <memory>

class Player : public GameObject
{
public:
    Player();
    ~Player();
    void setupPlayer(std::shared_ptr<ShaderResource> shaders, UI *ui);
    void ControllerInputs(float deltaTime, class CollisionHandler* collisionHandler, class Tilegrid *tilegrid, bool *restart, bool *quit);
    VectorMath2 GetPos();
    VectorMath2 GetDirection();
    void Dead();
    void DrawPlayer();

    bool isDead = false;
private:
    MatrixMath positionMatrix = Identity();
    MatrixMath rotationMatrix = Identity();

    GraphicsNode* playerObject;
    UI *ui;

    // Joystick deadzone
    float deadzone = 0.1;

    float movementSpeed = 1.5;
    float rotAngle = 0;
    float posX = 0;
    float posY = 0;

    // Controller input values
    float x = 0;
    float y = 0;
    float up = 0;
	float down = 0;
	float left = 0;
	float right = 0;
	float forward = 0;
	float backward = 0;

};
