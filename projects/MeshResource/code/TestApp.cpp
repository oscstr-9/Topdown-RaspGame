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
		player.tilePos = VectorMath2(tileX, tileY);
		player.size = 0.4;
		player.radius = player.size / 2;
		player.ID = id;
		player.objectType = ObjectType::PLAYER;
		tilegrid->tiles[tileY][tileX].gameObjects.push_back(&player);
	}

	void ExampleApp::spawnEnemyObject(int id, int tileX, int tileY)
	{	
		enemyWaves.push_back(new Enemy(shaders, tileToWorldPos(VectorMath2(tileX, tileY))));
		enemyWaves[enemyWaves.size() - 1]->tilePos = VectorMath2(tileX, tileY);
		enemyWaves[enemyWaves.size() - 1]->size = 0.4;
		enemyWaves[enemyWaves.size() - 1]->radius = enemyWaves[enemyWaves.size() - 1]->size / 2;
		enemyWaves[enemyWaves.size() - 1]->ID = id;
		enemyWaves[enemyWaves.size() - 1]->objectType = ObjectType::ENEMY;
		tilegrid->tiles[tileY][tileX].gameObjects.push_back(enemyWaves[enemyWaves.size() - 1]);
	}

	VectorMath2 ExampleApp::tileToWorldPos(VectorMath2 tilePos)
	{
		float posX = -((float)tilegrid->numOfX/2) * tilegrid->tileSize + tilegrid->tileSize / 2;
		float posY = -((float)tilegrid->numOfY/2) * tilegrid->tileSize + tilegrid->tileSize / 2;
		posX += tilePos.x * tilegrid->tileSize;
		posY += tilePos.y * tilegrid->tileSize;

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
			case GLFW_KEY_SPACE:
			if(action == GLFW_PRESS){
					//std::cout << "Fired a shot" << std::endl;
					if(collisionHandler->checkRayAgainstEnemies(player.GetPos(), player.GetDirection(), tilegrid, player.tilePos))
					{
						//std::cout << "Ray has hit an enemy" << std::endl;
						
					}
				}
				break;
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
			tilegrid = new Tilegrid(10, 10, -8, 0.5);
			tilegrid->createGraphics(shaders, true); // set to false to hide borders
			collisionHandler = new CollisionHandler();

			// Create player
			spawnPlayerObject(spawnID++, 1, tilegrid->numOfY / 2);
			player.setupPlayer(shaders);

			// Create enemies (should probably spawn in run loop instead)
			spawnEnemyObject(spawnID++, tilegrid->numOfX - 2, tilegrid->numOfY - 2);
			spawnEnemyObject(spawnID++, tilegrid->numOfX - 3, tilegrid->numOfY - 2);
			//spawnEnemyObject(spawnID++, tilegrid->numOfX - 2, tilegrid->numOfY - 2);
			spawnEnemyObject(spawnID++, tilegrid->numOfX - 5, tilegrid->numOfY - 2);
			spawnEnemyObject(spawnID++, tilegrid->numOfX - 6, tilegrid->numOfY - 2);
			

			// set ui rendering function
			// this->window->SetUiRender([this]()
			// {
			// 	this->ui.RenderUI();
			// });
			// this->ui.LoadScore();
			return true;
		}
		return false;
	}


std::vector<Enemy> ExampleApp::CreateSpawnWave(std::shared_ptr<ShaderResource> shader, MatrixMath viewMat, Tilegrid tilegrid){
    std::vector<Enemy> enemies;
    std::vector<Tile> freeSpawnTiles;
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
                    	freeSpawnTiles.push_back(tilegrid.tiles[y][x]);
                }
            }
        }
    
    for (int i = 0; i < 10 + pow(waveNum, 2); i++)
    {
		Tile spawnTile = freeSpawnTiles[rand() % freeSpawnTiles.size()];
        Enemy enemy = Enemy(shader, spawnTile.worldPos);
        enemies.push_back(enemy);
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

			// -------- Movement and collision --------
			// Controll character, includes wall collision detection
			player.ControllerInputs(deltaTime, collisionHandler, tilegrid);
			// Move player to other tile if necessary
			collisionHandler->updateTilePos(&player, tilegrid);
			for(int i = 0; i < enemyWaves.size(); i++)
			{
				// TODO: remove enemy that's been hit
				if(collisionHandler->hasHitEnemy)
				{
					if(collisionHandler->hitEnemyID == enemyWaves[i]->ID)
					{
						enemyWaves.erase(enemyWaves.begin() + i);
						collisionHandler->hasHitEnemy = false;
						continue;
					}
				}
				// Move enemies, including wall collision detection
				enemyWaves[i]->MoveToPoint(player.pos, deltaTime, collisionHandler, tilegrid);
				// Move enemies to other tiles if necessary
				collisionHandler->updateTilePos(enemyWaves[i], tilegrid);
			}
			// Player vs enemy collision in the tiles around player
			if(!enemyWaves.empty())
			{
				if(collisionHandler->hasCollidedWithEnemy(&player, tilegrid, enemyWaves[0]->size))
				{
					//std::cout << "Player has collided with enemy" << std::endl;
				}
			}
			// --------
			//player.GetDirection();
			

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
			for(int i = 0; i < enemyWaves.size(); i++){
				enemyWaves[i]->DrawEnemy();
			}

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