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

	void ExampleApp::spawnTestObject(int id)
	{
		TestObject* testObject = new TestObject();
		testObject->pos.x = 0;
		testObject->pos.y = 0;
		testObject->previousPos = testObject->pos;
		testObject->size = 0.2;
		testObject->ID = id;
		testObjects.push_back(testObject);

		Pos objectPos;
		objectPos.x = testObject->pos.x / testObject->size;
		objectPos.y = testObject->pos.y / testObject->size;
		tilegrid->tileInPos.at(objectPos).testObjects.push_back(testObject);

		collisionHandler->updateListOfTiles(&tilegrid->tileInPos.at(objectPos), tilegrid);
	}

	bool ExampleApp::Open()
	{
		App::Open();
		this->window = new Display::Window;
		window->SetKeyPressFunction([this](int32 keycode, int32, int32 action, int32)
			{
			// Adding keyboard functionality
			switch (keycode)
			{
			// case GLFW_KEY_W:
			// case GLFW_KEY_UP:
			// 	forward = action;
			// 	break;
			// case GLFW_KEY_A:
			// case GLFW_KEY_LEFT:
			// 	left = action;
			// 	break;
			// case GLFW_KEY_S:
			// case GLFW_KEY_DOWN:
			// 	backward = action;
			// 	break;
			// case GLFW_KEY_D:
			// case GLFW_KEY_RIGHT:
			// 	right = action;
			// 	break;
			// case GLFW_KEY_SPACE:
			// 	up = action;
			// 	break;
			// case GLFW_KEY_LEFT_SHIFT:
			// 	down = action;
			// 	break;
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
			//rotMat = 1;//RotateMatrix((M_PI/2), VectorMath3(1, 0, 0));

			window->GetSize(width, height);

			// set clear color (Background color)
			glClearColor(0.25f, 0.0f, 0.5f, 1.0f);

			// Find and load shaders
			shaders = std::make_shared<ShaderResource>();
			shaders->LoadShader("engine/render/VertShader.glsl","engine/render/FragShader.glsl");

			player.setupPlayer(shaders);

			// Create grid
			tilegrid = new Tilegrid(30, 30, -8, 0.2);
			tilegrid->createGraphics(shaders, true); // set to false to hide borders
			collisionHandler = new CollisionHandler();
			int id = 1;
			spawnTestObject(id++);
			spawnTestObject(id++);

			return true;
		}
		return false;
	}

	void ExampleApp::Run()
	{
		// Create camera
		ScreenCamera camera(90, width, height, 0.001, 100);
		camera.SetPosition(cameraPos);

		// Create light source
		Lighting light(VectorMath3(0, 0, 0), VectorMath3(1, 1, 1), 1);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		shaders->setVec4(VectorMath4(1, 1, 1, 1), "colorVector");

		float startTime = glfwGetTime();
		while (this->window->IsOpen())
		{
			float deltaTime = glfwGetTime() - startTime;
			startTime = glfwGetTime();

			std::cout << 1/deltaTime << std::endl;

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			this->window->Update();

			// Controll character

			quit = player.ControllerInputs(deltaTime, cameraPos);
			if(quit){
				this->window->Close();
			}

			// Update camera pos
			camera.SetRotMat(camRotMat);
			camera.SetPosition(cameraPos);

			// Bind light
			light.bindLight(shaders, camera.GetPosition());
			// Set projection-view-matrix
			shaders->setMat4(camera.GetProjViewMatrix(), "projectionViewMatrix");

			// -------- just testing collision -------- 
			for(int i = 0; i < testObjects.size(); i++)
			{
				testObjects[i]->previousPos = testObjects[i]->pos;
				testObjects[i]->pos.x += 0.05;
			}

			collisionHandler->handleCollisions(tilegrid);
			// -------- 

			// Draw to screen
			player.DrawPlayer();
			tilegrid->Draw();

			this->window->SwapBuffers();
		}
	}
}