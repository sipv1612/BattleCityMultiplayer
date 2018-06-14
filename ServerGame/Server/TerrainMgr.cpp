#include "TerrainMgr.h"


TerrainMgr* TerrainMgr::instance = 0;

TerrainMgr::TerrainMgr()
{
}


TerrainMgr::~TerrainMgr()
{
}

TerrainMgr * TerrainMgr::GetInstance()
{
	if (!instance)
	{
		instance = new TerrainMgr();
	}
	return instance;
}

void TerrainMgr::Update(float deltaTime)
{
}

void TerrainMgr::SpawnCommandBase(Team _team, float _x, float _y)
{
	auto terrain = new Terrain();
	terrain->SpawnTerrain(COMMANDBASE, _x, _y, _team);
	terrain->SetID(listTerrain.size());
	//terrain->AddDebug(this);
	listTerrain.push_back(terrain);
}

void TerrainMgr::Spawn(TerrianType type, float x, float y)
{
	auto terrain = new Terrain();
	terrain->SpawnTerrain(type, x, y);
	terrain->SetID(listTerrain.size());
	listTerrain.push_back(terrain);
}

std::vector<Terrain*> TerrainMgr::GetTerrains()
{
	return listTerrain;
}


