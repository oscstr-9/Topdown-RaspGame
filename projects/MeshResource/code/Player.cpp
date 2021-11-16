#include "Player.h"
#include "render/MESHRESOURCE.h"
#include "render/ShaderResource.h"
#include "CollisionHandler.h"
#include "Tilegrid.h"
#include "RenderDebug.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "UI.h"


Player::Player(){
}

Player::~Player(){
}

void Player::setupPlayer(std::shared_ptr<ShaderResource> shaders, UI *ui){
    // Find object textures
    std::shared_ptr<TextureResource> objTexture = std::make_shared<TextureResource>("pumpkin.png");
    // Load object textures
    objTexture->LoadFromFile();
    // Object meshes
    std::shared_ptr<MeshResource> objMesh = MeshResource::LoadObj("StarShip");
    // Object transform
    positionMatrix = MatrixMath::TranslationMatrix(VectorMath3(pos,-7)) * ScalarMatrix(VectorMath3(renderSize, renderSize, renderSize)) * RotateMatrix(M_PI/2, VectorMath3(1,0,0));
    // Object graphicnodes
    playerObject = new GraphicsNode(objMesh, objTexture, shaders, positionMatrix);

    this->ui = ui;
}

void Player::ControllerInputs(float deltaTime, CollisionHandler* collisionHandler, Tilegrid *tilegrid, bool *restart, bool *quit, bool *shoot){
    // Controller Inputs
    GLFWgamepadstate state;
    if(!isDead){
        // Button inputs
        if(glfwGetGamepadState(GLFW_JOYSTICK_1, &state)){

            if(state.axes[GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER] > -0.5){
                *shoot = true;
            }
            else{
                *shoot = false;
            }
        }
        // Joystick inputs
        if (state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y] > deadzone || state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y] < -deadzone){
            forward = state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y];
            if(!collisionHandler->hasCollidedWithWall(tilegrid, VectorMath2(pos.x, pos.y - forward * movementSpeed * deltaTime), size, tilePos))
            {
                pos.y -= forward * movementSpeed * deltaTime;
            }
        }
        else{
            forward = 0;
        }

        if (state.axes[GLFW_GAMEPAD_AXIS_LEFT_X] > deadzone || state.axes[GLFW_GAMEPAD_AXIS_LEFT_X] < -deadzone){
            right = state.axes[GLFW_GAMEPAD_AXIS_LEFT_X];
            if(!collisionHandler->hasCollidedWithWall(tilegrid, VectorMath2(pos.x + right * movementSpeed * deltaTime, pos.y), size, tilePos))
            {
                pos.x += right * movementSpeed * deltaTime;
            }
        }
        else{
            right = 0;
        }
        if (state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y] > deadzone || state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y] < -deadzone){
            y = state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y];
        }
        else{
            y = 0;
        }

        if (state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X] > deadzone || state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X] < -deadzone){
            x = state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X];
        }
        else{
            x = 0;
        }
        
        // If left joystick is unmoved look towards move direction
        if(x == 0 && y == 0){
            if(right != 0){
                rotAngle = -atan(forward / right)+M_PI/2;
                if(right < 0){
                    rotAngle += M_PI;
                }
            }
            else{
                if(forward < 0)
                    rotAngle = M_PI;
                else if(forward > 0)
                    rotAngle = 0;
            }
        }

        // look towards left joystick direction
        if (x != 0){
            rotAngle = -atan(y / x)+M_PI/2;
            if(x < 0){
                rotAngle += M_PI;
            }
        }
        else{
            if(y < 0)
                rotAngle = M_PI;
            else if(y>0)
                rotAngle = 0;
        }
        
        rotationMatrix = RotateMatrix(rotAngle, VectorMath3(0, 0, 1));
        positionMatrix =  MatrixMath::TranslationMatrix(VectorMath3(pos, -7)) * rotationMatrix * ScalarMatrix(VectorMath3(renderSize, renderSize, renderSize)) * RotateMatrix(M_PI/2, VectorMath3(1,0,0));

        playerObject->setTransform(positionMatrix);
    }
    else{
        if(glfwGetGamepadState(GLFW_JOYSTICK_1, &state)){
            if(state.buttons[GLFW_GAMEPAD_BUTTON_A]){
                *restart = true;
                isDead = false;
            }
            if (state.buttons[GLFW_GAMEPAD_BUTTON_START]){
                *quit = true;
            }
        }
    }
}

VectorMath2 Player::GetPos(){
    return pos;
}
VectorMath2 Player::GetDirection(){
    VectorMath4 rotationVector = rotationMatrix.VectorMultiplication(VectorMath4(1,1,1,1));
    rotationVector.Normalize();
    return VectorMath2(cos(rotAngle - M_PI/2), sin(rotAngle - M_PI/2));
}

void Player::Dead(){
    isDead = true;
    this->ui->SetIsDead(true);
}

void Player::DrawPlayer(){
    playerObject->Draw();
}