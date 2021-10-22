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

	void ExampleApp::spawnTestObject()
	{
		TestObject testObject;
		testObject.pos.x = 0;
		testObject.pos.y = 0;
		testObject.size = 0.2;
		testObject.ID = 1;
		testObjects.push_back(testObject);

		// gör detta för varje objekt, varje frame
		tilegrid->tileInPos.at(testObject.pos).testObjects.push_back(&testObject);
		collisionHandler->tilesToUpdate.push_back(&tilegrid->tileInPos.at(testObject.pos));
		
		
	}
	void ExampleApp::moveTestObjects()
	{
		// move it upwards every frame
		int x = testObjects[0].pos.x;
		int y = testObjects[0].pos.y;
		Pos previousPos;
		previousPos.x = x;
		previousPos.y = y;
		testObjects[0].pos.y += 0.05;

		// check if its pos is inside the tile for previous pos
		Tile* previousTile = &tilegrid->tileInPos.at(previousPos);
		// TODO: är denna collision test som spökar
		if(collisionHandler->pointInsideTile(testObjects[0].pos, previousTile->pos, previousTile->size))
		{
			// object is still inside its previous tile, no need to move it to another tile
		}
		else
		{
			// -------- Find neighbor tile to move to and move it --------
			bool hasFoundnewTile = false;
			for(int i = 0; i < previousTile->neighborGround.size(); i++)
			{
				Tile* groundTile = &previousTile->neighborGround[i];
				if(collisionHandler->AABBCollision(testObjects[0].pos, 0, groundTile->pos, groundTile->size))
				{
					// object is inside this tile
					hasFoundnewTile = true;
					// remove from previous tile
					// find testObject in tile to erase
					for(int j = 0; j < previousTile->testObjects.size(); j++)
					{
						if(testObjects[0].ID = previousTile->testObjects[j]->ID)
						{
							// found. erase from this vector
							previousTile->testObjects.erase(previousTile->testObjects.begin() + j);
						}
					}
					// move to this one and end search
					groundTile->testObjects.push_back(&testObjects[0]);
					bool isRegistered = false;
					for(int j = 0; j < collisionHandler->tilesToUpdate.size(); j++)
					{
						if(collisionHandler->tilesToUpdate[j]->pos == groundTile->pos)
						{
							// is the same, don't need to register this tile in the collisionHandler
							isRegistered = true;
							continue;
						}
					}
					if(!isRegistered)
					{
						collisionHandler->tilesToUpdate.push_back(groundTile);
						std::cout << "TestObject has moves" << std::endl;
					}
				}
			}
			// next tile is a wall, keep this object in this tile
			if(!hasFoundnewTile)
			{
				testObjects[0].pos.y -= 0.05;
			}
		}
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
			tilegrid = new Tilegrid(40, 40, -8, 0.2);
			tilegrid->createGraphics(shaders, true); // set to false to hide borders
			collisionHandler = new CollisionHandler();
			spawnTestObject();

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

			moveTestObjects();
			collisionHandler->handleCollisions();

			// Draw to screen
			player.DrawPlayer();
			tilegrid->Draw();

			this->window->SwapBuffers();
		}
	}
}