#include <fstream>
#include "GameManager.h"
#include "Define.h"
#include "Collision.h"

extern int YourPos;

GameManager* GameManager::instance = 0;

void GameManager::CheckCollsion(float deltaTime)
{
	TankVsBullet(deltaTime);
	TankVsTank(deltaTime);
	TankVsTerrain(deltaTime);
	BulletVsBullet(deltaTime);
	BulletVsTerrain(deltaTime);
}

void GameManager::TankVsTerrain(float deltaTime)
{
	Box broadPhaseBoxA, broadPhaseBoxB;
	float normalx = 0, normaly = 0;
	auto listTank = TankMgr::GetInstance()->GetTanks();
	auto listTerrain = TerrainManager::GetInstance()->GetTerrains();

	for (int i = 0; i < listTerrain.size(); i++)
	{
		for (int j = 0; j < listTank.size(); j++)
		{
			if (listTerrain.at(j)->IsDie() == false)
			{
				CollisionClass::GetSweptBroadphaseBox(listTank.at(j)->GetBox(), deltaTime, &broadPhaseBoxA);
				CollisionClass::GetSweptBroadphaseBox(listTerrain.at(j)->GetBox(), deltaTime, &broadPhaseBoxB);

				if (CollisionClass::AABBCheck(&broadPhaseBoxA, &broadPhaseBoxB))
				{
					float collisiontime = CollisionClass::SweptAABB(listTank.at(j)->GetBox(), listTerrain.at(j)->GetBox(), normalx, normaly, deltaTime);
					float remainingtime = 1 - collisiontime;
					if (remainingtime > 0)
					{
						listTank.at(j)->Move();
					}
				}
			}
		}
	}

}

void GameManager::TankVsTank(float deltaTime)
{
	Box broadPhaseBoxA, broadPhaseBoxB;
	float normalx = 0, normaly = 0;
	auto listTank = TankMgr::GetInstance()->GetTanks();
	//Tankk vs Tank
	for (int i = 0; i < listTank.size(); i++)
	{
		for (int j = i + 1; j < listTank.size(); j++)
		{
			CollisionClass::GetSweptBroadphaseBox(listTank.at(j)->GetBox(), deltaTime, &broadPhaseBoxA);
			CollisionClass::GetSweptBroadphaseBox(listTank.at(j)->GetBox(), deltaTime, &broadPhaseBoxB);

			if (CollisionClass::AABBCheck(&broadPhaseBoxA, &broadPhaseBoxB))
			{
				float collisiontime = CollisionClass::SweptAABB(listTank.at(j)->GetBox(), listTank.at(j)->GetBox(), normalx, normaly, deltaTime);
				float remainingtime = 1 - collisiontime;
				if (remainingtime > 0)
				{
					listTank.at(j)->Move();
					listTank.at(j)->Move();
				}
			}
		}
	}
}

void GameManager::TankVsBullet(float deltaTime)
{
	Box broadPhaseBoxA, broadPhaseBoxB;
	float normalx = 0, normaly = 0;
	auto listTank = TankMgr::GetInstance()->GetTanks();
	auto listBullet = BulletManager::GetInstance()->GetBullets();

	for (int i = 0; i < listTank.size(); i++)
	{
		for (int j = 0; j < listBullet.size(); j++)
		{
			if (listBullet.at(j)->GetTeam() != listTank.at(j)->GetTeam() && !listBullet.at(j)->IsDie())
			{
				CollisionClass::GetSweptBroadphaseBox(listBullet.at(j)->GetBox(), deltaTime, &broadPhaseBoxA);
				CollisionClass::GetSweptBroadphaseBox(listTank.at(j)->GetBox(), deltaTime, &broadPhaseBoxB);

				if (CollisionClass::AABBCheck(&broadPhaseBoxA, &broadPhaseBoxB))
				{
					float collisiontime = CollisionClass::SweptAABB(listBullet.at(j)->GetBox(), listTank.at(j)->GetBox(), normalx, normaly, deltaTime);
					float remainingtime = 1 - collisiontime;
					if (remainingtime > 0)
					{
						listBullet.at(j)->AABBHandle(deltaTime, collisiontime);
						listBullet.at(j)->Die();
						listTank.at(j)->Die();
					}
				}

			}
		}
	}
}

void GameManager::BulletVsTerrain(float deltaTime)
{
	Box broadPhaseBoxA, broadPhaseBoxB;
	float normalx = 0, normaly = 0;
	auto listBullet = BulletManager::GetInstance()->GetBullets();
	auto listTerrain = TerrainManager::GetInstance()->GetTerrains();
	for (int i = 0; i < listTerrain.size(); i++)
	{

		for (int j = 0; j < listBullet.size(); j++)
		{
			if (!listBullet.at(j)->IsDie() && !listTerrain.at(j)->IsDie())
			{
				CollisionClass::GetSweptBroadphaseBox(listBullet.at(j)->GetBox(), deltaTime, &broadPhaseBoxA);
				CollisionClass::GetSweptBroadphaseBox(listTerrain.at(j)->GetBox(), deltaTime, &broadPhaseBoxB);

				if (CollisionClass::AABBCheck(&broadPhaseBoxA, &broadPhaseBoxB))
				{
					float collisiontime = CollisionClass::SweptAABB(listBullet.at(j)->GetBox(), listTerrain.at(j)->GetBox(), normalx, normaly, deltaTime);
					float remainingtime = 1 - collisiontime;
					if (remainingtime > 0)
					{
						listBullet.at(j)->AABBHandle(deltaTime, collisiontime);
						listBullet.at(j)->Die();
						if (listTerrain.at(j)->GetType() == TerrainType::BRICK)
							listTerrain.at(j)->Die();
					}
				}
			}
		}
	}
}

void GameManager::BulletVsBullet(float deltaTime)
{
	Box broadPhaseBoxA, broadPhaseBoxB;
	float normalx = 0, normaly = 0;
	auto listBullet = BulletManager::GetInstance()->GetBullets();

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

GameManager * GameManager::create()
{
	GameManager *pRet = new(std::nothrow) GameManager();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

bool GameManager::init()
{
	if (!Node::init())
		return false;
	InitMap();
	this->addChild(BulletManager::GetInstance());
	this->addChild(TankMgr::GetInstance());
	this->addChild(TerrainManager::GetInstance());
	return true;
}

GameManager * GameManager::GetInstance()
{
	if (!instance)
	{
		instance = new GameManager();
	}
	return instance;
}

void GameManager::InitMap()
{
	Team characterTeam = Team::TeamBlue;
	if(YourPos <= 1)

	TankMgr::GetInstance()->InitPlayers();
	int ** matrixMap = LoadMap();
	if (matrixMap != nullptr)
	{
		for (int i = 0; i < MAP_HEIGHT; i++)
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				if (matrixMap[i][j] == MAP_TERRAIN_SLIVER)
				{
					TerrainManager::GetInstance()->Spawn(TerrainType::CONCRETE, j * MAP_TILED_SIZE, i * MAP_TILED_SIZE);
				}
				if (matrixMap[i][j] == MAP_TERRAIN_RED)
				{
					TerrainManager::GetInstance()->Spawn(TerrainType::BRICK, j * MAP_TILED_SIZE, i * MAP_TILED_SIZE);

				}
				if (matrixMap[i][j] == MAP_TANK_TEAM_1)
				{
					TankMgr::GetInstance()->Spawn(Team::TeamBlue, j * MAP_TILED_SIZE, i * MAP_TILED_SIZE);
				}
				if (matrixMap[i][j] == MAP_TANK_TEAM_2)
				{
					TankMgr::GetInstance()->Spawn(Team::TeamGreen, j * MAP_TILED_SIZE, i * MAP_TILED_SIZE);
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

int** GameManager::LoadMap()
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

void GameManager::Update(float deltaTime)
{
	CheckCollsion(deltaTime);
	TankMgr::GetInstance()->Update(deltaTime);
	BulletManager::GetInstance()->Update(deltaTime);
}
