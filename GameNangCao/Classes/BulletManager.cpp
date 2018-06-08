#include "BulletManager.h"


void BulletManager::Init(std::vector<TANK_STATE*> *_allTank, std::vector<BULLET_STATE*> *_allBullet, std::vector<BRICK*> *_allBrick)
{
	
	bList = ListBullet();
	for (int i = 0; i < 100; i++) {
		bList.push_back(new Bullet(_allTank,_allBullet,_allBrick));
	}
	
}


void BulletManager::Get(Owned type, float x, float y, eMove emove)
{
	/*for (int i = 0; i < bList.size(); i++)
	{
		if (bList[i]->isVisible() == false)
		{	
			bList[i]->Init(x, y, 0, emove, type);
			break;
		}
	}*/
}

BulletManager::BulletManager()
{
}

BulletManager::~BulletManager()
{
}

void BulletManager::WorldUpdate()
{

}

ListBullet BulletManager::getList()
{
	return bList;
}


