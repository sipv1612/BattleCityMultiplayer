#pragma once
#ifndef TERRAIN_MANAGER
#define TERRAIN_MANAGER
#include "TerrainObject.h"

class TerrainManager : public Node
{
private:
	Vector<TerrainObject*> listTerrain;
	static TerrainManager * instance;
	TerrainObject *teamBlue, *teamGreen;
public:
	static TerrainManager* create();
	static TerrainManager* GetInstance();
	bool init();
	void SpawnCommandBase(Team _team, float _x, float _y);
	void Spawn(TerrainType type, float x, float y);
	void HandleDiePackage(TERRAIN_DIE package);
	Vector<TerrainObject* >GetTerrains();
};
#endif // !TERRAIN_MANAGER