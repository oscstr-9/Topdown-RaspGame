#include "Player.h"
#include "render/MESHRESOURCE.h"
#include "render/ShaderResource.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

Player::Player(){
}

Player::~Player(){
}

void Player::setupPlayer(std::shared_ptr<ShaderResource> shaders){
    // Find object textures
    std::shared_ptr<TextureResource> objTexture = std::make_shared<TextureResource>("monkehTexture.png");
    // Load object textures
    objTexture->LoadFromFile();
    // Object meshes
    std::shared_ptr<MeshResource> objMesh = MeshResource::LoadObj("smoothMonkeh");
    // Object transform
    positionMatrix = MatrixMath::TranslationMatrix(VectorMath3(0, 0,-7)) * ScalarMatrix(VectorMath3(0.2, 0.2, 0.2)) * RotateMatrix(M_PI/2, VectorMath3(1,0,0));
    // Object graphicnodes
    playerObject = new GraphicsNode(objMesh, objTexture, shaders, positionMatrix);
}

bool Player::ControllerInputs(float deltatTime, VectorMath3 &cameraPos){
    // Controller Inputs
    GLFWgamepadstate state;

    // Button inputs
    if(glfwGetGamepadState(GLFW_JOYSTICK_1, &state)){
        if(state.buttons[GLFW_GAMEPAD_BUTTON_A]){
            std::cout << "A" << std::endl;
            movementSpeed += 0.1;
        }
        else{
            up = false;
        }
        if(state.buttons[GLFW_GAMEPAD_BUTTON_B]){
            std::cout << "B" << std::endl;
            movementSpeed -= 0.1;
            if (movementSpeed <= 0.2){
                movementSpeed = 0.2;
            }
        }
        else{
            down = false;
        }
        if(state.axes[GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER] > -0.5){
            std::cout << "Trigger" << std::endl;

        }
        if(state.buttons[GLFW_GAMEPAD_BUTTON_BACK]){
            std::cout << "Back" << std::endl;
        }
        if (state.buttons[GLFW_GAMEPAD_BUTTON_START]){
            quit = true;
        }
    }
    // Joystick inputs
    if (state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y] > deadzone || state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y] < -deadzone){
        forward = state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y];
        posY -= forward * movementSpeed * deltatTime;
    }
    else{
        forward = 0;
    }

    if (state.axes[GLFW_GAMEPAD_AXIS_LEFT_X] > deadzone || state.axes[GLFW_GAMEPAD_AXIS_LEFT_X] < -deadzone){
        right = state.axes[GLFW_GAMEPAD_AXIS_LEFT_X];
        posX += right * movementSpeed * deltatTime;
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
    if (x != 0){
        rotAngle = -atan(y / x)+M_PI/2;
        if(x < 0){
            rotAngle += M_PI;
        }
    }
    else{
        if(y<0)
            rotAngle = M_PI;
        else if(y>0)
            rotAngle = 0;
    }
    
    rotationMatrix = RotateMatrix(rotAngle, VectorMath3(0, 0, 1));
    posX = pos.x;
    posY = pos.y;
    positionMatrix =  MatrixMath::TranslationMatrix(VectorMath3(posX, posY, -7)) * rotationMatrix * ScalarMatrix(VectorMath3(0.2, 0.2, 0.2)) * RotateMatrix(M_PI/2, VectorMath3(1,0,0));

    //positionMatrix = MatrixMath::TranslationMatrix((VectorMath3(-right, forward, 0) )) * positionMatrix * rotationMatrix;
    playerObject->setTransform(positionMatrix);
    cameraPos = VectorMath3(-posX, -posY + 0.5, cameraPos.z);
    return quit;
}

MatrixMath Player::GetPos(){
    return positionMatrix;
}

// convert from graphics pos to grid pos
void Player::setRenderPos()
{
    // posX = pos.x;
    // posY = pos.y;
}

void Player::DrawPlayer(){
    playerObject->Draw();
}