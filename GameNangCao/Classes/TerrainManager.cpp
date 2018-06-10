#include "TerrainManager.h"

TerrainManager* TerrainManager::instance = 0;

TerrainManager * TerrainManager::create()
{
	TerrainManager *pRet = new(std::nothrow) TerrainManager();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

TerrainManager * TerrainManager::GetInstance()
{
	if (!instance)
	{
		instance =  TerrainManager::create();
	}
	return instance;
}

bool TerrainManager::init()
{
	if (!Node::init())
		return false;
	return true;
}


void TerrainManager::Spawn(TerrainType type, float x, float y)
{
	auto terrain = TerrainObject::create();
	terrain->SpawnTerrain(type, x, y);
	terrain->SetID(listTerrain.size());
	//terrain->AddDebug(this);
	listTerrain.pushBack(terrain);
	addChild(terrain);
}

void TerrainManager::HandleDiePackage(TERRAIN_DIE package)
{
	auto terrain = listTerrain.at(package.idTerrain);
	terrain->Die();
	//terrain->rectNode->setVisible(false);
}

Vector<TerrainObject*> TerrainManager::GetTerrains()
{
	return listTerrain;
}
