#include "TerrainManager.h"
#include "EndScene.h"

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

void TerrainManager::SpawnCommandBase(Team _team, float _x, float _y)
{
	auto terrain = TerrainObject::create();
	terrain->SpawnTerrain(COMMANDBASE, _x, _y, _team);
	terrain->SetID(listTerrain.size());
	//terrain->AddDebug(this);
	listTerrain.pushBack(terrain);
	addChild(terrain);
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

	if (terrain->GetType() == TerrainType::COMMANDBASE)
	{
		Scene *endScene = EndScene::createScene(terrain->GetTeam());
		Director::getInstance()->replaceScene(endScene);
	}
}

Vector<TerrainObject*> TerrainManager::GetTerrains()
{
	return listTerrain;
}
