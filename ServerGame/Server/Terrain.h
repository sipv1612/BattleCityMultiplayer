#pragma once
#include "Object.h"
class Terrain :
	public Object
{
private:
	TerrianType type;
public:
	Terrain();
	~Terrain();

	void Die();
	void SendDataDie();
	void SpawnTerrain(TerrianType type, float x, float y, Team _team = Team::TEAM_NONE);

	TerrianType GetType();


};

