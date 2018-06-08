#pragma once
#include "BulletMgr.h"
#include "TankMgr.h"
#include "TerrainMgr.h"
class GameMgr
{
private:

	static GameMgr * instance;

	GameMgr();
	void CheckCollsion(float deltaTime);
	void TankVsTerrain(float deltaTime);
	void TankVsTank(float deltaTime);
	void TankVsBullet(float deltaTime);
	void BulletVsTerrain(float deltaTime);
	void BulletVsBullet(float deltaTime);
	void InitMap();
	int** LoadMap();
public:
	~GameMgr();
	static GameMgr * GetInstance();
	void Update(float deltaTime);
};

