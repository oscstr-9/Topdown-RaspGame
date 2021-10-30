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
		player.previousPos = player.pos;
		player.tilePos = VectorMath2(tileX, tileY);
		player.size = 0.4;
		player.ID = id;
		player.objectType = ObjectType::PLAYER;
		gameObjects.push_back(&player);
		tilegrid->tiles[tileY][tileX].gameObjects.push_back(&player);
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
	}

	VectorMath2 ExampleApp::tileToWorldPos(VectorMath2 tilePos)
	{
		float posX = -((float)tilegrid->numOfX/2) * tilegrid->tileSize + tilegrid->tileSize / 2;
		float posY = -((float)tilegrid->numOfY/2) * tilegrid->tileSize + tilegrid->tileSize / 2;
		posX += tilePos.x * tilegrid->tileSize;
		posY += tilePos.y * tilegrid->tileSize;

		return VectorMath2(posX, posY);
	}
	VectorMath2 ExampleApp::worldToTilePos(VectorMath2 worldPos)
	{
		// worldPos(0, 0) in tilePos
		// int posX = -((worldPos.x + tilegrid->tileSize / 2) / tilegrid->tileSize) * 2;
		// int posY = -((worldPos.y + tilegrid->tileSize / 2) / tilegrid->tileSize) * 2;
		// add on worldPos
		

		return VectorMath2(0, 0);
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
			tilegrid = new Tilegrid(5, 3, -8, 0.5);
			tilegrid->createGraphics(shaders, true); // set to false to hide borders
			collisionHandler = new CollisionHandler();

			// Create player
			spawnPlayerObject(spawnID++, tilegrid->numOfX/2, tilegrid->numOfY/2);
			player.setupPlayer(shaders);

			// Create enemies (should probably spawn in run loop instead)
			//spawnEnemyObject(spawnID++, tilegrid->numOfX/2 + 6, tilegrid->numOfY/2 + 6);
			

			return true;
		}
		return false;
	}


std::vector<Enemy> ExampleApp::CreateSpawnWave(std::shared_ptr<ShaderResource> shader, MatrixMath viewMat, Tilegrid tilegrid){
    std::vector<Enemy> enemies;
    std::vector<VectorMath2> freeSpawnLoactions;
    srand(time(NULL));

    for (int x = 0; x < tilegrid.numOfX; x++)
    {
        for (int y = 0; y < tilegrid.numOfY; y++)
            {
                VectorMath4 cullingPos = VectorMath4(tilegrid.tiles[y][x].worldPos.x, tilegrid.tiles[y][x].worldPos.y, -7, 1);
                cullingPos = viewMat.VectorMultiplication(cullingPos);
                cullingPos.x /= cullingPos.w;
                cullingPos.y /= cullingPos.w;

                if(cullingPos.x > 1.1 || cullingPos.x < -1.1 || cullingPos.y > 1 || cullingPos.y < -1.2){
					if(tilegrid.tiles[y][x].type == Type::GROUND)
                    	freeSpawnLoactions.push_back(VectorMath2(tilegrid.tiles[y][x].worldPos.x, tilegrid.tiles[y][x].worldPos.y));
                }
            }
        }
    
    for (int i = 0; i < 10 + pow(waveNum, 2); i++)
    {
        Enemy enemy = Enemy(shader, freeSpawnLoactions[rand() % freeSpawnLoactions.size()]);
        enemies.push_back(enemy);
		gameObjects.push_back(&enemy);
    }
    waveNum++;
    return enemies;
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

		float startTime = glfwGetTime();
		float spawntimer = glfwGetTime();
		//enemyWaves = CreateSpawnWave(shaders, camera.GetProjViewMatrix(), *tilegrid);
		while (this->window->IsOpen())
		{
			// if(enemyWaves.size() == 0){
			// 	enemyWaves = CreateSpawnWave(shaders, camera.GetProjViewMatrix(), *tilegrid);
			// }
			float deltaTime = glfwGetTime() - startTime;
			startTime = glfwGetTime();


			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			this->window->Update();

			// Controll character
			// Check wall collision inside controllerinputs
			player.ControllerInputs(deltaTime, collisionHandler, tilegrid);
			// TODO: 2. move player to other tile if necessary
			
			// TODO: 3. move enemies (include wall collision here)
			// TODO: 4. move enemies to other tiles if necessary
			// TODO: 5. check enemy collision

			//enemy.MoveToPoint(player.GetPos(), deltaTime);

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

			// Draw to screen
			player.DrawPlayer();
			tilegrid->Draw(camera.GetProjViewMatrix());
			// for (int i = 0; i < enemyWaves.size()-1; i++){
			// 	enemyWaves[i].MoveToPoint(player.GetPos(), deltaTime);
			// 	enemyWaves[i].DrawEnemy();
			// }

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