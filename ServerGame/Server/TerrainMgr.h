#pragma once
#include "Terrain.h"

class TerrainMgr
{
private:
	std::vector<Terrain*> listTerrain;
	static TerrainMgr * instance;
	TerrainMgr();
public:
	~TerrainMgr();

	static TerrainMgr* GetInstance();
	void Update(float deltaTime);
	void Spawn(TerrianType type, float x, float y);
	std::vector<Terrain* >GetTerrains();
};

