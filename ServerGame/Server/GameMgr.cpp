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
	TankVsTerrain(deltaTime);
	BulletVsBullet(deltaTime);
	BulletVsTerrain(deltaTime);
}

void GameMgr::TankVsTerrain(float deltaTime)
{
	Box broadPhaseBoxA, broadPhaseBoxB;
	float normalx = 0, normaly = 0;
	auto listTank = TankMgr::GetInstance()->GetTanks();
	auto listTerrain = TerrainMgr::GetInstance()->GetTerrains();
	
	for (int i = 0; i < listTerrain.size(); i++)
	{
		for (int j = 0; j < listTank.size(); j++)
		{
			if (listTerrain[i]->IsDie() == false)
			{
				CollisionClass::GetSweptBroadphaseBox(listTank[j]->GetBox(), deltaTime, &broadPhaseBoxA);
				CollisionClass::GetSweptBroadphaseBox(listTerrain[i]->GetBox(), deltaTime, &broadPhaseBoxB);

				if (CollisionClass::AABBCheck(&broadPhaseBoxA, &broadPhaseBoxB))
				{
					float collisiontime = CollisionClass::SweptAABB(listTank[j]->GetBox(), listTerrain[i]->GetBox(), normalx, normaly, deltaTime);
					float remainingtime = 1 - collisiontime;
					if (remainingtime > 0)
					{
						listTank[j]->Move();
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
			CollisionClass::GetSweptBroadphaseBox(listTank[j]->GetBox(), deltaTime, &broadPhaseBoxA);
			CollisionClass::GetSweptBroadphaseBox(listTank[i]->GetBox(), deltaTime, &broadPhaseBoxB);

			if (CollisionClass::AABBCheck(&broadPhaseBoxA, &broadPhaseBoxB))
			{
				float collisiontime = CollisionClass::SweptAABB(listTank[j]->GetBox(), listTank[i]->GetBox(), normalx, normaly, deltaTime);
				float remainingtime = 1 - collisiontime;
				if (remainingtime > 0)
				{
					listTank[j]->Move();
					listTank[i]->Move();
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
			if (listBullet[j]->GetTeam() != listTank[i]->GetTeam() && !listBullet[j]->IsDie())
			{
				CollisionClass::GetSweptBroadphaseBox(listBullet[j]->GetBox(), deltaTime, &broadPhaseBoxA);
				CollisionClass::GetSweptBroadphaseBox(listTank[i]->GetBox(), deltaTime, &broadPhaseBoxB);

				if (CollisionClass::AABBCheck(&broadPhaseBoxA, &broadPhaseBoxB))
				{
					float collisiontime = CollisionClass::SweptAABB(listBullet[j]->GetBox(), listTank[i]->GetBox(), normalx, normaly, deltaTime);
					float remainingtime = 1 - collisiontime;
					if (remainingtime > 0)
					{
						listBullet[j]->AABBHandle(deltaTime, collisiontime);
						listBullet[j]->Die();
						listTank[i]->Die();
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
			if (!listBullet[j]->IsDie() && !listTerrain[i]->IsDie())
			{
				CollisionClass::GetSweptBroadphaseBox(listBullet[j]->GetBox(), deltaTime, &broadPhaseBoxA);
				CollisionClass::GetSweptBroadphaseBox(listTerrain[i]->GetBox(), deltaTime, &broadPhaseBoxB);

				if (CollisionClass::AABBCheck(&broadPhaseBoxA, &broadPhaseBoxB))
				{
					float collisiontime = CollisionClass::SweptAABB(listBullet[j]->GetBox(), listTerrain[i]->GetBox(), normalx, normaly, deltaTime);
					float remainingtime = 1 - collisiontime;
					if (remainingtime > 0)
					{
						listBullet[j]->AABBHandle(deltaTime, collisiontime);
						listBullet[j]->Die();
						if (listTerrain[i]->GetType() == REB)
							listTerrain[i]->Die();
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
			if (!listBullet[j]->IsDie() && !listBullet[i]->IsDie())
			{
				CollisionClass::GetSweptBroadphaseBox(listBullet[j]->GetBox(), deltaTime, &broadPhaseBoxA);
				CollisionClass::GetSweptBroadphaseBox(listBullet[i]->GetBox(), deltaTime, &broadPhaseBoxB);

				if (CollisionClass::AABBCheck(&broadPhaseBoxA, &broadPhaseBoxB))
				{
					float collisiontime = CollisionClass::SweptAABB(listBullet[j]->GetBox(), listBullet[i]->GetBox(), normalx, normaly, deltaTime);
					float remainingtime = 1 - collisiontime;
					if (remainingtime > 0)
					{
						listBullet[j]->AABBHandle(deltaTime, collisiontime);
						listBullet[j]->Die();
						listBullet[i]->AABBHandle(deltaTime, collisiontime);
						listBullet[i]->Die();

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
	CheckCollsion(deltaTime);
	TankMgr::GetInstance()->Update(deltaTime);
	BulletMgr::GetInstance()->Update(deltaTime);
}
