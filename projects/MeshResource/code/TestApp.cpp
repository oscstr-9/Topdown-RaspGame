//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2020 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
//#include <stb_image.h>
#include <cstring>
#include "config.h"
#include "TestApp.h"
#include "render/MESHRESOURCE.h"
#include "render/TextureResource.h"
#include "render/ShaderResource.h"
#include "core/MatrixMath.h"
#include "render/Camera.h"
#include "render/Lighting.h"

using namespace Display;
namespace Example
{
	ExampleApp::ExampleApp()
	{/*cool*/}

	ExampleApp::~ExampleApp()
	{/*so cool*/}
	bool ExampleApp::Open()
	{
		App::Open();
		this->window = new Display::Window;
		window->SetKeyPressFunction([this](int32 keycode, int32, int32 action, int32)
			{
			// Adding keyboard functionality
			switch (keycode)
			{
			case GLFW_KEY_W:
			case GLFW_KEY_UP:
				forward = action;
				break;
			case GLFW_KEY_A:
			case GLFW_KEY_LEFT:
				left = action;
				break;
			case GLFW_KEY_S:
			case GLFW_KEY_DOWN:
				backward = action;
				break;
			case GLFW_KEY_D:
			case GLFW_KEY_RIGHT:
				right = action;
				break;
			case GLFW_KEY_SPACE:
				up = action;
				break;
			case GLFW_KEY_LEFT_SHIFT:
				down = action;
				break;
			case GLFW_KEY_ESCAPE:
				this->window->Close();
				break;
			default:
				break;
			}
			});
		// Adding mouse functionality
		window->SetMouseMoveFunction([this](double x, double y) {
			//rotMat = RotateMatrix(((height / 2) - y) * -speed, VectorMath3(1, 0, 0))*RotateMatrix(((width/2)-x)*-speed, VectorMath3(0,1,0));
		});
		
		if (this->window->Open())
		{
			window->GetSize(width, height);

			// set clear color (Background color)
			glClearColor(0.5f, 1.0f, 0.8f, 1.0f);

			// Find and load shaders
			shaders = std::make_shared<ShaderResource>();
			shaders->LoadShader("engine/render/VertShader.glsl","engine/render/FragShader.glsl");

			// Find object textures
			std::shared_ptr<TextureResource> testTexture = std::make_shared<TextureResource>("moon.png");
			std::shared_ptr<TextureResource> objTexture = std::make_shared<TextureResource>("monkehTexture.png");

			// Load object textures
			testTexture->LoadFromFile();
			objTexture->LoadFromFile();

			// Object meshes
			std::shared_ptr<MeshResource> sphereMesh = MeshResource::LoadObj("moon2");
			std::shared_ptr<MeshResource> objMesh = MeshResource::LoadObj("smoothMonkeh");

			// Object transforms
			MatrixMath sphereTransform = Identity();
			MatrixMath objTransform = characterPosMat * ScalarMatrix(VectorMath3(0.5, 0.5, 0.5));

			// Object graphicnodes
			sphere = new GraphicsNode(sphereMesh, testTexture, shaders, sphereTransform);
			objObject = new GraphicsNode(objMesh, objTexture, shaders, objTransform);

			tilegrid = new Tilegrid(4, 4, -8, 1);
			tilegrid->createGraphics(shaders, true); // set to false to hide borders
			
			std::shared_ptr<MeshResource> cubeMesh = MeshResource::Cube(50);
			cube = new GraphicsNode(cubeMesh, testTexture, shaders, objTransform);

			return true;
		}
		return false;
	}

	void ExampleApp::ControllerInputs(){
		// Controller Inputs
		GLFWgamepadstate state;
		if(glfwGetGamepadState(GLFW_JOYSTICK_1, &state)){
			if(state.buttons[GLFW_GAMEPAD_BUTTON_A]){
				std::cout << "A" << std::endl;
				up = true;
			}
			else{
				up = false;
			}
			if(state.buttons[GLFW_GAMEPAD_BUTTON_B]){
				std::cout << "B" << std::endl;
				down = true;
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
				this->window->Close();
			}
		}
		if (state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y] > deadZone || state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y] < -deadZone){
			backward = state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y];
		}
		else{
			backward = 0;
		}

		if (state.axes[GLFW_GAMEPAD_AXIS_LEFT_X] > deadZone || state.axes[GLFW_GAMEPAD_AXIS_LEFT_X] < -deadZone){
			right = state.axes[GLFW_GAMEPAD_AXIS_LEFT_X];
		}
		else{
			right = 0;
		}
		if (state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y] > deadZone || state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y] < -deadZone){
			y = state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y];
		}
		else{
			y = 0;
		}
		if (state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X] > deadZone || state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X] < -deadZone){
			x = state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X];
		}
		else{
			x = 0;
		}
	}

	void ExampleApp::Run()
	{
		// Create camera
		ScreenCamera camera(90, width, height, 0.001, 100);
		camera.SetPosition(posVec);

		Lighting light(VectorMath3(3, 0, 0), VectorMath3(1, 1, 1), 0.5);

		float lP = 0;

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		
		shaders->setVec4(VectorMath4(1, 1, 1, 1), "colorVector");

		while (this->window->IsOpen())
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			this->window->Update();

			ControllerInputs();
			posVec = posVec + (VectorMath3((left - right), (down - up), (forward - backward)).NormalizeNew() * 0.08);

			lP+=0.01;
			light.setPos(VectorMath3(cos(lP)*8, 0, -sin(lP)*8));
			sphere->setTransform(MatrixMath::TranslationMatrix(VectorMath3(cos(lP)*8, 0, -sin(lP)*8)) * RotateMatrix(lP, VectorMath3(0, 1, 0)) * RotateMatrix(M_PI/2, VectorMath3(0,0,1)) *  ScalarMatrix(VectorMath3(0.005, 0.005, 0.005)));

			camera.SetRotMat(rotMat);
			camera.SetPosition(posVec);
			light.bindLight(shaders, camera.GetPosition());

			shaders->setMat4(camera.GetProjViewMatrix(), "projectionViewMatrix");
			
			characterPosMat = characterPosMat * MatrixMath::TranslationMatrix(VectorMath3(x/4, -y/4, 0));
			objObject->setTransform(characterPosMat);


			this->objObject->Draw();
			this->sphere->Draw();
			sphere->setTransform(MatrixMath::TranslationMatrix(VectorMath3(-sin(lP) * 8, 0, cos(lP) * 8)) * RotateMatrix(-lP-(M_PI/2), VectorMath3(0, 1, 0)) * RotateMatrix(M_PI / 2, VectorMath3(0, 0, 1)) * ScalarMatrix(VectorMath3(0.005, 0.005, 0.005)));

			this->sphere->Draw();

			tilegrid->Draw();

			this->cube->Draw();
			this->window->SwapBuffers();
		}
	}
}