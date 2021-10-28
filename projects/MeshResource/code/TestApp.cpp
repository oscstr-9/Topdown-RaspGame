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
#include "RenderDebug.h"

using namespace Display;
namespace Example
{
	ExampleApp::ExampleApp()
	{/*cool*/}
	ExampleApp::~ExampleApp()
	{/*so cool*/}

	void ExampleApp::spawnPlayerObject(int id, int tileX, int tileY)
	{
		player.pos = tileToWorldPos(VectorMath2(tileX, tileY));
		player.pos.PrintVector();
		player.previousPos = player.pos;
		player.size = 0.2;
		player.ID = id;
		player.objectType = ObjectType::PLAYER;
		gameObjects.push_back(&player);

		tilegrid->tileInPos.at(VectorMath2(tileX, tileY)).gameObjects.push_back(&player);
		tilegrid->playerTile = &tilegrid->tileInPos.at(VectorMath2(tileX, tileY));

		collisionHandler->updateListOfTiles(&tilegrid->tileInPos.at(VectorMath2(tileX, tileY)), tilegrid);
	}

	void ExampleApp::spawnEnemyObject(int id, int tileX, int tileY)
	{	
		enemy = Enemy(shaders, VectorMath2(0,0));
		enemy.pos = tileToWorldPos(VectorMath2(tileX, tileY));
		enemy.previousPos = enemy.pos;
		enemy.size = 0.2;
		enemy.ID = id;
		enemy.objectType = ObjectType::ENEMY;
		gameObjects.push_back(&enemy);

		tilegrid->tileInPos.at(VectorMath2(tileX, tileY)).gameObjects.push_back(&enemy);

		collisionHandler->updateListOfTiles(&tilegrid->tileInPos.at(VectorMath2(tileX, tileY)), tilegrid);
	}

	VectorMath2 ExampleApp::tileToWorldPos(VectorMath2 tilePos)
	{
		// tile (0, 0) in worldPos
		float posX = -(tilegrid->numOfX - 1) * tilegrid->tileInPos.at(VectorMath2(0, 0)).size;
		float posY = -(tilegrid->numOfY - 1) * tilegrid->tileInPos.at(VectorMath2(0, 0)).size;
		// add on tilePos
		posX += tilePos.x * 2 * tilegrid->tileInPos.at(VectorMath2(0, 0)).size;
		posY += tilePos.y * 2 * tilegrid->tileInPos.at(VectorMath2(0, 0)).size;

		return VectorMath2(posX, posY);
	}
	VectorMath2 ExampleApp::worldToTilePos(VectorMath2 worldPos)
	{
		// tile (0, 0) in tilePos
		float posX = 0;
		float posY = 0;
		// add on tilePos
		

		return VectorMath2(posX, posY);
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
			// case GLFW_KEY_S:square
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
			case GLFW_KEY_F1:{
				if(action == GLFW_PRESS){
					debug = !debug;
					std::cout << debug << std::endl;
				}
			}
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
			//rotMat = 1;//RotateMatrix((M_PI/2), VectorMath3(1, 0, 0));

			window->GetSize(width, height);

			// set clear color (Background color)
			glClearColor(0.25f, 0.0f, 0.5f, 1.0f);

			// Find and load shaders
			shaders = std::make_shared<ShaderResource>();
			shaders->LoadShader("engine/render/VertShader.glsl","engine/render/FragShader.glsl");

			// Create grid
			tilegrid = new Tilegrid(40, 40, -8, 0.4);
			tilegrid->createGraphics(shaders, true); // set to false to hide borders
			collisionHandler = new CollisionHandler();

			// Create player
			spawnPlayerObject(spawnID++, tilegrid->numOfX/2, tilegrid->numOfY/2);
			player.setupPlayer(shaders);

			// Create enemies (should probably spawn in run loop instead)
			spawnEnemyObject(spawnID++, tilegrid->numOfX/2 + 6, tilegrid->numOfY/2 + 6);
			

			return true;
		}
		return false;
	}

	void ExampleApp::Run()
	{
		// Create camera
		ScreenCamera camera(90, width, height, 0.001, 100);
		camera.SetPosition(cameraPos);

		ScreenCamera debugCamera(90, width, height, 0.001, 100);
		debugCamera.SetPosition(debugCameraPos);

		// Create light source
		Lighting light(VectorMath3(0, 0, 0), VectorMath3(1, 1, 1), 1);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		shaders->setVec4(VectorMath4(1, 1, 1, 1), "colorVector");

		Enemy enemyWaves;
		enemyWaves.CreateSpawnWave(shaders, camera.GetProjViewMatrix(), *tilegrid);

		float startTime = glfwGetTime();
		while (this->window->IsOpen())
		{
			float deltaTime = glfwGetTime() - startTime;
			startTime = glfwGetTime();

			//std::cout << 1/deltaTime << std::endl;

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			this->window->Update();

			// Controll character

			player.ControllerInputs(deltaTime);
			VectorMath2 endRay = player.pos - VectorMath2(10, 0);

			enemy.MoveToPoint(player.GetPos(), deltaTime);

			// Update camera pos
			cameraPos = VectorMath3(player.pos + VectorMath2(0, -3), -1);
			camera.SetRotMat(camRotMat);
			camera.SetPosition(cameraPos);

			debugCamera.SetPosition(-debugCameraPos);
			debugCamera.SetRotMat(debugCamRotMat);
			if(debug){
				shaders->setMat4(debugCamera.GetProjViewMatrix(), "projectionViewMatrix");
			}
			else{
				shaders->setMat4(camera.GetProjViewMatrix(), "projectionViewMatrix");
			}

			// Bind light
			light.bindLight(shaders, camera.GetPosition());
			// Set projection-view-matrix

			// After all input and GameObject updates are done, handle collision
			//collisionHandler->checkRayAgainstEnemies(player.pos, endRay, tilegrid);
			collisionHandler->handleCollisions(tilegrid);

			// Draw to screen
			player.DrawPlayer();
			enemy.DrawEnemy();
			tilegrid->Draw(camera.GetProjViewMatrix());

			if(debug){
				Debug::Render(debugCamera.GetProjViewMatrix());
			}
			else{
				Debug::Render(camera.GetProjViewMatrix());
			}

			this->window->SwapBuffers();
		}
	}
}