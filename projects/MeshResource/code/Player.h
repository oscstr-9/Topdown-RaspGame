#pragma once
#include "core/VectorMath.h"
#include "core/MatrixMath.h"
#include "render/GraphicsNode.h"
#include <memory>



class Player
{
public:
    Player();
    ~Player();
    void setupPlayer(std::shared_ptr<ShaderResource> shaders);
    bool ControllerInputs(float deltaTime, VectorMath3 &cameraPos);
    MatrixMath GetPos();
    void DrawPlayer();
private:
    MatrixMath positionMatrix = Identity();
    MatrixMath rotationMatrix = Identity();

    GraphicsNode* playerObject;

    // Joystick deadzone
    float deadzone = 0.2;

    float movementSpeed = 1;
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
    bool quit = false;
};
