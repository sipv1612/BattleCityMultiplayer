#include <fstream>
#include "GameMgr.h"
#include "Define.h"
#include "Collision.h"


GameMgr* GameMgr::instance = 0;
GameMgr::GameMgr()
{
	InitMap();
}

void GameMgr::CheckCollsion(float deltaTime)
{
	TankVsBullet(deltaTime);
	TankVsTank(deltaTime);
	BulletVsBullet(deltaTime);
	BulletVsTerrain(deltaTime);
	TankVsTerrain(deltaTime);
}

void GameMgr::TankVsTerrain(float deltaTime)
{
	Box broadPhaseBoxA, broadPhaseBoxB;
	float normalx = 0, normaly = 0;
	auto listTank = TankMgr::GetInstance()->GetTanks();
	auto listTerrain = TerrainMgr::GetInstance()->GetTerrains();
	
	for (int i = 0; i < listTank.size(); i++)
	{
		for (int j = 0; j < listTerrain.size(); j++)
		{
			if (!listTerrain.at(j)->IsDie() && !listTank.at(i)->IsDie())
			{
				CollisionClass::GetSweptBroadphaseBox(listTank.at(i)->GetBox(), deltaTime, &broadPhaseBoxA);
				CollisionClass::GetSweptBroadphaseBox(listTerrain.at(j)->GetBox(), deltaTime, &broadPhaseBoxB);

				if (CollisionClass::AABBCheck(&broadPhaseBoxA, &broadPhaseBoxB))
				{
					float collisiontime = CollisionClass::SweptAABB(listTank.at(i)->GetBox(), listTerrain.at(j)->GetBox(), normalx, normaly, deltaTime);
					float remainingtime = 1 - collisiontime;
					if (remainingtime > 0)
					{
						listTank.at(i)->Move();

					}
				}
			}
		}
	}

}

void GameMgr::TankVsTank(float deltaTime)
{
	Box broadPhaseBoxA, broadPhaseBoxB;
	float normalx = 0, normaly = 0;
	auto listTank = TankMgr::GetInstance()->GetTanks();
	//Tankk vs Tank
	for (int i = 0; i < listTank.size(); i++)
	{
		for (int j = i + 1; j < listTank.size(); j++)
		{
			if (!listTank.at(i)->IsDie() && !listTank.at(j)->IsDie())
			{
				CollisionClass::GetSweptBroadphaseBox(listTank.at(i)->GetBox(), deltaTime, &broadPhaseBoxA);
				CollisionClass::GetSweptBroadphaseBox(listTank.at(j)->GetBox(), deltaTime, &broadPhaseBoxB);

				if (CollisionClass::AABBCheck(&broadPhaseBoxA, &broadPhaseBoxB))
				{
					float collisiontime = CollisionClass::SweptAABB(listTank.at(i)->GetBox(), listTank.at(j)->GetBox(), normalx, normaly, deltaTime);
					float remainingtime = 1 - collisiontime;
					if (remainingtime > 0)
					{
						listTank.at(i)->Move();
						listTank.at(j)->Move();
					}
				}
			}
		}
	}
}

void GameMgr::TankVsBullet(float deltaTime)
{
	Box broadPhaseBoxA, broadPhaseBoxB;
	float normalx = 0, normaly = 0;
	auto listTank = TankMgr::GetInstance()->GetTanks();
	auto listBullet = BulletMgr::GetInstance()->GetBullets();

	for (int i = 0; i < listTank.size(); i++)
	{
		for (int j = 0; j < listBullet.size(); j++)
		{
			if (listBullet.at(j)->GetTeam() != listTank.at(i)->GetTeam() && !listBullet.at(j)->IsDie() && !listTank.at(i)->IsDie())
			{
				CollisionClass::GetSweptBroadphaseBox(listBullet.at(j)->GetBox(), deltaTime, &broadPhaseBoxA);
				CollisionClass::GetSweptBroadphaseBox(listTank.at(i)->GetBox(), deltaTime, &broadPhaseBoxB);

				if (CollisionClass::AABBCheck(&broadPhaseBoxA, &broadPhaseBoxB))
				{
					float collisiontime = CollisionClass::SweptAABB(listBullet.at(j)->GetBox(), listTank.at(i)->GetBox(), normalx, normaly, deltaTime);
					float remainingtime = 1 - collisiontime;
					if (remainingtime > 0)
					{
						listBullet.at(j)->AABBHandle(deltaTime, collisiontime);
						listBullet.at(j)->Die();
						listTank.at(i)->Die();
					}
				}

			}
		}
	}
}

void GameMgr::BulletVsTerrain(float deltaTime)
{
	Box broadPhaseBoxA, broadPhaseBoxB;
	float normalx = 0, normaly = 0;
	auto listBullet = BulletMgr::GetInstance()->GetBullets();
	auto listTerrain = TerrainMgr::GetInstance()->GetTerrains();
	for (int i = 0; i < listTerrain.size(); i++)
	{

		for (int j = 0; j < listBullet.size(); j++)
		{
			if (!listBullet.at(j)->IsDie() && !listTerrain.at(i)->IsDie())
			{
				CollisionClass::GetSweptBroadphaseBox(listBullet.at(j)->GetBox(), deltaTime, &broadPhaseBoxA);
				CollisionClass::GetSweptBroadphaseBox(listTerrain.at(i)->GetBox(), deltaTime, &broadPhaseBoxB);

				if (CollisionClass::AABBCheck(&broadPhaseBoxA, &broadPhaseBoxB))
				{
					float collisiontime = CollisionClass::SweptAABB(listBullet.at(j)->GetBox(), listTerrain.at(i)->GetBox(), normalx, normaly, deltaTime);
					float remainingtime = 1 - collisiontime;
					if (remainingtime > 0)
					{
						listBullet.at(j)->AABBHandle(deltaTime, collisiontime);
						listBullet.at(j)->Die();
						if (listTerrain.at(i)->GetType() == TerrianType::REB)
							listTerrain.at(i)->Die();
					}
				}
			}
		}
	}
}

void GameMgr::BulletVsBullet(float deltaTime)
{
	Box broadPhaseBoxA, broadPhaseBoxB;
	float normalx = 0, normaly = 0;
	auto listBullet = BulletMgr::GetInstance()->GetBullets();

	//bullet vs bullet
	for (int i = 0; i < listBullet.size(); i++)
	{
		for (int j = i + 1; j < listBullet.size(); j++)
		{
			if (!listBullet.at(j)->IsDie() && !listBullet.at(i)->IsDie())
			{
				CollisionClass::GetSweptBroadphaseBox(listBullet.at(j)->GetBox(), deltaTime, &broadPhaseBoxA);
				CollisionClass::GetSweptBroadphaseBox(listBullet.at(i)->GetBox(), deltaTime, &broadPhaseBoxB);

				if (CollisionClass::AABBCheck(&broadPhaseBoxA, &broadPhaseBoxB))
				{
					float collisiontime = CollisionClass::SweptAABB(listBullet.at(j)->GetBox(), listBullet.at(i)->GetBox(), normalx, normaly, deltaTime);
					float remainingtime = 1 - collisiontime;
					if (remainingtime > 0)
					{
						listBullet.at(j)->AABBHandle(deltaTime, collisiontime);
						listBullet.at(j)->Die();
						listBullet.at(i)->AABBHandle(deltaTime, collisiontime);
						listBullet.at(i)->Die();

					}
				}
			}
		}
	}
}



GameMgr::~GameMgr()
{
}

GameMgr * GameMgr::GetInstance()
{
	if (!instance)
	{
		instance = new GameMgr();
	}
	return instance;
}

void GameMgr::InitMap()
{
	TankMgr::GetInstance()->SpawnPlayer();
	int ** matrixMap = LoadMap();
	if (matrixMap != nullptr)
	{
		for (int i = 0; i < MAP_HEIGHT; i++)
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				if (matrixMap[i][j] == MAP_TERRAIN_SLIVER)
				{
					TerrainMgr::GetInstance()->Spawn(TerrianType::SILVER, j * MAP_TILED_SIZE, i * MAP_TILED_SIZE);
				}
				if (matrixMap[i][j] == MAP_TERRAIN_RED)
				{
					TerrainMgr::GetInstance()->Spawn(TerrianType::REB, j * MAP_TILED_SIZE, i * MAP_TILED_SIZE);
					
				}
				if (matrixMap[i][j] == MAP_TANK_TEAM_1)
				{
					TankMgr::GetInstance()->SpawnRobot(TEAM_1, j * MAP_TILED_SIZE, i * MAP_TILED_SIZE);
				}
				if (matrixMap[i][j] == MAP_TANK_TEAM_2)
				{
					TankMgr::GetInstance()->SpawnRobot(TEAM_2, j * MAP_TILED_SIZE, i * MAP_TILED_SIZE);
				}
				/*if (matrixMap[i][j] == MAP_BIRTH_TEAM_1)
				{
					birth[0] = new Birth();
					birth[0]->Init(TEAM_1, j * 32, i * 32);
				}
				if (matrixMap[i][j] == MAP_BIRTH_TEAM_2)
				{
					birth[1] = new Birth();
					birth[1]->Init(TEAM_2, j * 32, i * 32);
				}*/
			}
	}
	else
	{
		printf("Load Map failed!!\n");
	}
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		delete[] matrixMap[i];
	}
	delete[] matrixMap;
}

int** GameMgr::LoadMap()
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
		matrix = new int*[MAP_HEIGHT];
		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			matrix[i] = new int[MAP_WIDTH];
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				tileMap >> matrix[i][j];
			}
		}
	}


	return matrix;
}

void GameMgr::Update(float deltaTime)
{
	TankMgr::GetInstance()->Packing();
	TankMgr::GetInstance()->UpdateAIRobot(deltaTime);
	CheckCollsion(deltaTime);
	TankMgr::GetInstance()->Update(deltaTime);
	BulletMgr::GetInstance()->Update(deltaTime);
}
