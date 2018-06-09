#pragma once
#ifndef TERRAIN_MANAGER
#define TERRAIN_MANAGER
#include "TerrainObject.h"

class TerrainManager : public Node
{
private:
	Vector<TerrainObject*> listTerrain;
	static TerrainManager * instance;
public:
	static TerrainManager* create();
	static TerrainManager* GetInstance();
	bool init();
	void Spawn(TerrainType type, float x, float y);
	void HandleDiePackage(TERRAIN_DIE package);
	Vector<TerrainObject* >GetTerrains();
};
#endif // !TERRAIN_MANAGER