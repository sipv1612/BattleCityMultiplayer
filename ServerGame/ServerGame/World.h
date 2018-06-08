#pragma once
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include "Tank.h"
#include "TerrianObject.h"
#include "Collision.h"
#include "Define.h"
#include "Birth.h"

extern UPDATE_WORLD _world;
class GameData
{
public:
	TerrianObject** terrian;
	int nTerrian;
	Bullet** bullet;
	int nBullet;
	PlayerTank** playerTank;
	
};


class World {
private:
	Box* broadPhaseBoxA;
	Box* broadPhaseBoxB;
	Birth * birth[2];
	int LPHead[4];
	float deltaTime[12];
	int _Move[8];

public:
	/*TerrianObject** terrian;
	int nTerrian;
	Bullet** bullet;
	int nBullet;
	PlayerTank** playerTank;*/
	GameData* gameData;
	
	World()
	{
		
		gameData = new GameData();
		_world.teamWin = 0;
		
		for (int i = 0; i < 4; i++)
		{
			LPHead[i] = 0;
		}
		for (int i = 0; i < 12; i++)
		{
			deltaTime[i] = 0;
		}
		for (int i = 0; i < 8; i++)
		{
			_Move[i] = 0;
		}
#pragma region Tank
		gameData->playerTank = new PlayerTank*[12];
		gameData->playerTank[0] = new PlayerTank(&_world.allBullet, &_world.allTank, &_world.allBrick, TEAM_1, 320, 50, TANK_SIZE, TANK_SIZE, NONE);
		gameData->playerTank[1] = new PlayerTank(&_world.allBullet, &_world.allTank, &_world.allBrick, TEAM_1, 465, 50, TANK_SIZE, TANK_SIZE, NONE);
		gameData->playerTank[2] = new PlayerTank(&_world.allBullet, &_world.allTank, &_world.allBrick, TEAM_2, 465, 688, TANK_SIZE, TANK_SIZE, NONE);
		gameData->playerTank[3] = new PlayerTank(&_world.allBullet, &_world.allTank, &_world.allBrick, TEAM_2, 320, 688, TANK_SIZE, TANK_SIZE, NONE);
		


#pragma endregion Tank

#pragma region Bullet
		
		gameData->nBullet = 100;
		gameData->bullet = new Bullet*[100];
		for (int i = 0; i < gameData->nBullet; i++)
		{
			gameData->bullet[i] = new Bullet(&_world.allBullet, &_world.allTank, &_world.allBrick);
		}
#pragma endregion Bullet

#pragma region Terrian
		gameData->nTerrian = 0;
		gameData->terrian = new TerrianObject*[300];
		int** tileMap = Map();
		int nRobot = 4;
		if (tileMap != nullptr)
		{
			for (int i = 0; i < 23; i++)
				for (int j = 0; j < 25; j++)
				{
							
					if (tileMap[i][j] == 3)
					{
						gameData->terrian[gameData->nTerrian] = new TerrianObject(&_world.allBullet, &_world.allTank, &_world.allBrick);
						gameData->terrian[gameData->nTerrian]->Init(TerrianType::SILVER, j * 32, i * 32);
						gameData->nTerrian++;
					}
					if (tileMap[i][j] == 1)
					{
						gameData->terrian[gameData->nTerrian] = new TerrianObject(&_world.allBullet, &_world.allTank, &_world.allBrick);
						gameData->terrian[gameData->nTerrian]->Init(TerrianType::REB, j * 32, i * 32);
						gameData->nTerrian++;
					}
					if (tileMap[i][j] == 5)
					{
						gameData->playerTank[nRobot] = new PlayerTank(&_world.allBullet, &_world.allTank, &_world.allBrick, TEAM_1, j*32, i*32, 27, 27, NONE);
						nRobot++;
					}
					if (tileMap[i][j] == 4)
					{
						gameData->playerTank[nRobot] = new PlayerTank(&_world.allBullet, &_world.allTank, &_world.allBrick, TEAM_2, j * 32, i * 32, 27, 27, NONE);
						nRobot++;
					}
					if (tileMap[i][j] == 6) 
					{
						birth[0] = new Birth();
						birth[0]->Init(TEAM_1, j * 32, i * 32);
					}
					if (tileMap[i][j] == 2)
					{
						birth[1] = new Birth();
						birth[1]->Init(TEAM_2, j * 32, i * 32);
					}

				}
		}
#pragma endregion Terrian
	}
	int** Map()
	{
		int **matrix = 0;
		std::ifstream tileMap("Map.txt");
		if (!tileMap.is_open())
		{
			printf("Load Map Error !!!!!!!!!\n");
			return nullptr;
		}
		else
		{
			matrix = new int*[23];
			for (int i = 0; i < 23; i++)
			{
				matrix[i] = new int[25];
				for (int j = 0; j < 25; j++)
				{
					tileMap >> matrix[i][j];
				}
			}
		}
		
		
		return matrix;
	}
	void Collision(float dt)
	{
		broadPhaseBoxA = new Box();
		broadPhaseBoxB = new Box();
		float normalx = 0, normaly = 0;

		//player vs terrian
		for (int i = 0; i < gameData->nTerrian; i++)
		{
			for (int j = 0; j < 12; j++)
			{
				if (gameData->terrian[i]->getState().isDie == false)
				{
					CollisionClass::GetSweptBroadphaseBox(gameData->playerTank[j]->GetBox(), dt, broadPhaseBoxA);
					CollisionClass::GetSweptBroadphaseBox(gameData->terrian[i]->GetBox(), dt, broadPhaseBoxB);

					if (CollisionClass::AABBCheck(broadPhaseBoxA, broadPhaseBoxB))
					{
						float collisiontime = CollisionClass::SweptAABB(gameData->playerTank[j]->GetBox(), gameData->terrian[i]->GetBox(), normalx, normaly, dt);
						float remainingtime = 1 - collisiontime;
						if (remainingtime > 0)
						{
							gameData->playerTank[j]->GetBox()->vx = 0;
							gameData->playerTank[j]->GetBox()->vy = 0;
						}
					}
				}
			}
		}


		//bullet vs terrian
		for (int i = 0; i < gameData->nTerrian; i++)
		{

			for (int j = 0; j < gameData->nBullet; j++)
			{
				if (gameData->bullet[j]->getState().isVisible && gameData->terrian[i]->getState().isDie == false)
				{
					CollisionClass::GetSweptBroadphaseBox(gameData->bullet[j]->GetBox(), dt, broadPhaseBoxA);
					CollisionClass::GetSweptBroadphaseBox(gameData->terrian[i]->GetBox(), dt, broadPhaseBoxB);

					if (CollisionClass::AABBCheck(broadPhaseBoxA, broadPhaseBoxB))
					{
						float collisiontime = CollisionClass::SweptAABB(gameData->bullet[j]->GetBox(), gameData->terrian[i]->GetBox(), normalx, normaly, dt);
						float remainingtime = 1 - collisiontime;
						if (remainingtime > 0)
						{
							
							gameData->bullet[j]->GetBox()->x += gameData->bullet[j]->GetBox()->vx * collisiontime * dt;
							gameData->bullet[j]->GetBox()->y += gameData->bullet[j]->GetBox()->vy * collisiontime * dt;
							gameData->bullet[j]->GetBox()->vx = 0;
							gameData->bullet[j]->GetBox()->vy = 0;
							gameData->bullet[j]->Done();
							if (gameData->terrian[i]->GetType() == REB)
								gameData->terrian[i]->Done();
						}
					}
				}
			}
		}

		//bullet vs bullet
		for (int i = 0; i < gameData->nBullet; i++)
		{
			for (int j = i + 1; j < gameData->nBullet; j++)
			{
				if (gameData->bullet[j]->getState().isVisible && gameData->bullet[i]->getState().isVisible)
				{
					CollisionClass::GetSweptBroadphaseBox(gameData->bullet[j]->GetBox(), dt, broadPhaseBoxA);
					CollisionClass::GetSweptBroadphaseBox(gameData->bullet[i]->GetBox(), dt, broadPhaseBoxB);

					if (CollisionClass::AABBCheck(broadPhaseBoxA, broadPhaseBoxB))
					{
						float collisiontime = CollisionClass::SweptAABB(gameData->bullet[j]->GetBox(), gameData->bullet[i]->GetBox(), normalx, normaly, dt);
						float remainingtime = 1 - collisiontime;
						if (remainingtime > 0)
						{
							gameData->bullet[j]->GetBox()->x += gameData->bullet[j]->GetBox()->vx * collisiontime * dt;
							gameData->bullet[j]->GetBox()->y += gameData->bullet[j]->GetBox()->vy * collisiontime * dt;
							gameData->bullet[j]->GetBox()->vx = 0;
							gameData->bullet[j]->GetBox()->vy = 0;
							gameData->bullet[j]->Done();
							gameData->bullet[i]->GetBox()->x += gameData->bullet[j]->GetBox()->vx * collisiontime * dt;
							gameData->bullet[i]->GetBox()->y += gameData->bullet[j]->GetBox()->vy * collisiontime * dt;
							gameData->bullet[i]->GetBox()->vx = 0;
							gameData->bullet[i]->GetBox()->vy = 0;
							gameData->bullet[i]->Done();

						}
					}
				}
			}
		}

		//Tankk vs Tank
		for (int i = 0; i < 12; i++)
		{
			for (int j = i + 1; j < 12; j++)
			{
				CollisionClass::GetSweptBroadphaseBox(gameData->playerTank[j]->GetBox(), dt, broadPhaseBoxA);
				CollisionClass::GetSweptBroadphaseBox(gameData->playerTank[i]->GetBox(), dt, broadPhaseBoxB);

				if (CollisionClass::AABBCheck(broadPhaseBoxA, broadPhaseBoxB))
				{
					float collisiontime = CollisionClass::SweptAABB(gameData->playerTank[j]->GetBox(), gameData->playerTank[i]->GetBox(), normalx, normaly, dt);
					float remainingtime = 1 - collisiontime;
					if (remainingtime > 0)
					{
						
						gameData->playerTank[j]->GetBox()->vx = 0;
						gameData->playerTank[j]->GetBox()->vy = 0;
						gameData->playerTank[i]->GetBox()->vx = 0;
						gameData->playerTank[i]->GetBox()->vy = 0;
					}
				}
			}
		}

		//Tank vs bullet
		for (int i = 0; i < 12; i++)
		{
			for (int j = 0; j < gameData->nBullet; j++)
			{
				if (gameData->bullet[j]->getOwn() != gameData->playerTank[i]->getOwn() && gameData->bullet[j]->getState().isVisible)
				{
					CollisionClass::GetSweptBroadphaseBox(gameData->bullet[j]->GetBox(), dt, broadPhaseBoxA);
					CollisionClass::GetSweptBroadphaseBox(gameData->playerTank[i]->GetBox(), dt, broadPhaseBoxB);

					if (CollisionClass::AABBCheck(broadPhaseBoxA, broadPhaseBoxB))
					{
						float collisiontime = CollisionClass::SweptAABB(gameData->bullet[j]->GetBox(), gameData->playerTank[i]->GetBox(), normalx, normaly, dt);
						float remainingtime = 1 - collisiontime;
						if (remainingtime > 0)
						{
							gameData->bullet[j]->GetBox()->x += gameData->bullet[j]->GetBox()->vx * collisiontime * dt;
							gameData->bullet[j]->GetBox()->y += gameData->bullet[j]->GetBox()->vy * collisiontime * dt;
							gameData->bullet[j]->GetBox()->vx = 0;
							gameData->bullet[j]->GetBox()->vy = 0;
							gameData->bullet[j]->Done();
							gameData->playerTank[i]->Die();
						}
					}

				}
			}
		}
		//Birth vs bullet
		for (int i = 0; i < gameData->nBullet; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (gameData->bullet[i]->getOwn() != birth[j]->getType() && gameData->bullet[i]->getState().isVisible)
				{
					CollisionClass::GetSweptBroadphaseBox(gameData->bullet[i]->GetBox(), dt, broadPhaseBoxA);
					CollisionClass::GetSweptBroadphaseBox(birth[j]->GetBox(), dt, broadPhaseBoxB);

					if (CollisionClass::AABBCheck(broadPhaseBoxA, broadPhaseBoxB))
					{
						float collisiontime = CollisionClass::SweptAABB(gameData->bullet[i]->GetBox(), birth[j]->GetBox(), normalx, normaly, dt);
						float remainingtime = 1 - collisiontime;
						if (remainingtime > 0)
						{
							gameData->bullet[i]->GetBox()->x += gameData->bullet[j]->GetBox()->vx * collisiontime * dt;
							gameData->bullet[i]->GetBox()->y += gameData->bullet[j]->GetBox()->vy * collisiontime * dt;
							gameData->bullet[i]->GetBox()->vx = 0;
							gameData->bullet[i]->GetBox()->vy = 0;
							gameData->bullet[i]->Done();
							if (birth[j]->getType() == TEAM_1)
								_world.teamWin = (unsigned int) 2;
							else
								_world.teamWin = (unsigned int) 1;
							
						}
					}
				}
			}
		}
	}

	//AI Robot
	void AIRobot(float dt)
	{
		for (int i = 4; i < 12; i++)
		{
			if (gameData->playerTank[i]->isDie() == false)
			{
				deltaTime[i] += dt;
				if (deltaTime[i] > 2)
				{
					//srand(time(NULL));
					_Move[i - 4] = rand() % 4 + 1;
					switch (_Move[i - 4])
					{
					case 1:
						gameData->playerTank[i]->Move(UP, ROBOT_SPEED);
						gameData->playerTank[i]->Shoot(gameData->bullet, gameData->nBullet, UP);
						break;
					case 2:
						gameData->playerTank[i]->Move(DOWN, ROBOT_SPEED);
						gameData->playerTank[i]->Shoot(gameData->bullet, gameData->nBullet, DOWN);
						break;
					case 3:
						gameData->playerTank[i]->Move(LEFT, ROBOT_SPEED);
						gameData->playerTank[i]->Shoot(gameData->bullet, gameData->nBullet, LEFT);
						break;
					case 4:
						gameData->playerTank[i]->Move(RIGHT, ROBOT_SPEED);
						gameData->playerTank[i]->Shoot(gameData->bullet, gameData->nBullet, RIGHT);
						break;
					default:
						break;
					}
					deltaTime[i] = 0;
				}
				
			}
		}
	}
	void Update(float dt)
	{
		
		for (int i = 0; i < DataSrc::numOfPlayer; i++)
		{
			if (LPHead[i] + BYTE_OF_CLIENT <= DataSrc::dataRecv[i]->GetIndex())
			{
				TANK_STATE *temp = new TANK_STATE();
				memcpy(temp, DataSrc::dataRecv[i]->GetData() + LPHead[i], sizeof TANK_STATE);
				if (temp != nullptr)
				{
					gameData->playerTank[i]->Move(temp->Move, TANK_SPEED);
					if (temp->Shooting)
					{
						gameData->playerTank[i]->Shoot(gameData->bullet, gameData->nBullet, temp->SideShoot);
					}
				}
				LPHead[i] += BYTE_OF_CLIENT;
			}
			else
				if (LPHead[i] + BYTE_OF_CLIENT > CMD_BUFSIZE)
					LPHead[i] = 0;
		}
	
		AIRobot(dt);
		
		Collision(dt);

		//update player
		for (int i = 0; i < 12; i++)
		{
			gameData->playerTank[i]->Update(dt);
			
		}

		//update bullet
		for (int i = 0; i < gameData->nBullet; i++)
		{
			gameData->bullet[i]->Update(dt);
		}

		
		
	}



};