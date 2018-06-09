#ifndef TERRAIN_OBJECT
#define TERRAIN_OBJECT
#include "BaseObject.h"

class TerrainObject : public BaseObject
{
private:
	TerrainType type;
public:
	static TerrainObject* create();
	bool init();
	void SpawnTerrain(TerrainType _type, float _x, float _y);
	TerrainType GetType();
};
#endif // !TERRAIN_OBJECT