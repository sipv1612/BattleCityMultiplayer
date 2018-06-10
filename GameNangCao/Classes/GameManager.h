#ifndef GAME_MANAGER
#define GAME_MANAGER

#include "BulletManager.h"
#include "TerrainManager.h"
#include "TankMgr.h"

class GameManager : public Node
{
private:

	static GameManager * instance;
	void CheckCollsion(float deltaTime);
	void TankVsTerrain(float deltaTime);
	void TankVsTank(float deltaTime);
	void TankVsBullet(float deltaTime);
	void BulletVsTerrain(float deltaTime);
	void BulletVsBullet(float deltaTime);
	
	void InitMap();
	int** LoadMap();
public:
	static GameManager* create();
	bool init();
	static GameManager * GetInstance();
	void Update(float deltaTime);
	
};
#endif