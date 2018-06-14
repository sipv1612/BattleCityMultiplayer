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

	float timeCheckPing = 0;
	float timeBeforeCheckPing = 0;
public:
	static GameManager* create();
	bool init();
	void UpdateCheckPingTime(float deltaTime);
	void SendDataCheckPing();
	static GameManager * GetInstance();
	void HandlePing(int iD);
	void Update(float deltaTime);
	
};
#endif