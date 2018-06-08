#include "Terrain.h"
#include "GlobalVariable.h"


Terrain::Terrain()
{
	SetBoxSize(TERRIAN_SIZE, TERRIAN_SIZE);
}


Terrain::~Terrain()
{
}

void Terrain::Die()
{
	isDie = true;
	SendDataDie();
}

void Terrain::SendDataDie()
{
	PACKET_KEY key = PACKET_KEY(TerrainDie);
	memcpy(dataSendBuffer + LPDataSendBuffer, &key, sizeof PACKET_KEY);
	LPDataSendBuffer += sizeof PACKET_KEY;
	TERRAIN_DIE data = TERRAIN_DIE(iD);
	memcpy(dataSendBuffer + LPDataSendBuffer, &data, sizeof TERRAIN_DIE);
	LPDataSendBuffer += sizeof TERRAIN_DIE;
	//printf("Terrain Die \n");

}

void Terrain::SpawnTerrain(TerrianType _type, float x, float y)
{
	type = _type;

	SetPos(x, y);
}


TerrianType Terrain::GetType()
{
	return type;
}
