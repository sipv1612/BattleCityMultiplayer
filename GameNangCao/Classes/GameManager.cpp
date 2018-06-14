#include <fstream>
#include "GameManager.h"
#include "Define.h"
#include "Collision.h"
#include "GlobalVariable.h"

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
						//listTank.at(i)->Die();
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
						//if (listTerrain.at(i)->GetType() == TerrainType::BRICK)
							//listTerrain.at(i)->Die();
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
	this->addChild(BulletManager::GetInstance());
	this->addChild(TankMgr::GetInstance());
	this->addChild(TerrainManager::GetInstance());
	this->InitMap();

	GameTime = 0;

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

void GameManager::HandlePing(int iD)
{
	if (iD == YourPos)
	{
		float ping = GameTime - timeBeforeCheckPing;
	}
}

void GameManager::InitMap()
{
	
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
					TerrainManager::GetInstance()->Spawn(TerrainType::BRICK, j * MAP_TILED_SIZE,  i * MAP_TILED_SIZE);

				}
				if (matrixMap[i][j] == MAP_TANK_TEAM_BLUE)
				{
					TankMgr::GetInstance()->Spawn(Team::TeamBlue, j * MAP_TILED_SIZE, i * MAP_TILED_SIZE);
				}
				if (matrixMap[i][j] == MAP_TANK_TEAM_GREEN)
				{
					TankMgr::GetInstance()->Spawn(Team::TeamGreen, j * MAP_TILED_SIZE, i * MAP_TILED_SIZE);
				}
				if (matrixMap[i][j] == MAP_BIRTH_TEAM_BLUE)
				{
					TerrainManager::GetInstance()->SpawnCommandBase(Team::TeamBlue, j * MAP_TILED_SIZE, i * MAP_TILED_SIZE);
				}
				if (matrixMap[i][j] == MAP_BIRTH_TEAM_GREEN)
				{
					TerrainManager::GetInstance()->SpawnCommandBase(Team::TeamGreen, j * MAP_TILED_SIZE, i * MAP_TILED_SIZE);
				}
			}
	}
	else
	{
		printf("Load Map failed!!\n");
	}
}
void GameManager::UpdateCheckPingTime(float deltaTime)
{
	timeCheckPing += deltaTime;
	if (timeCheckPing > CHECK_PING_RATE)
	{
		SendDataCheckPing();
		timeCheckPing = GameTime;
		timeCheckPing = 0;
	}
}
void GameManager::SendDataCheckPing()
{
	SEND_KEY key = SEND_KEY(KeySend::Ping);
	memcpy(dataSendBuffer + LPDataSendBuffer, &key, sizeof SEND_KEY);
	LPDataSendBuffer += sizeof SEND_KEY;
	GET_PING data = GET_PING(YourPos, GameTime);
	memcpy(dataSendBuffer + LPDataSendBuffer, &data, sizeof GET_PING);
	LPDataSendBuffer += sizeof GET_PING;
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
	GameTime += deltaTime;
	UpdateCheckPingTime(deltaTime);
}




