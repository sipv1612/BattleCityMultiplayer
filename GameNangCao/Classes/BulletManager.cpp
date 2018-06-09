#include "BulletManager.h"

BulletManager* BulletManager::instance = 0;

Bullet * BulletManager::GetNewBullet()
{
	for (int i = 0; i < listBullet.size(); i++)
	{
		if (listBullet.at(i)->IsDie())
		{
			return listBullet.at(i);
		}
	}
	auto bullet = new Bullet();
	bullet->SetID(listBullet.size());
	listBullet.pushBack(bullet);
	return bullet;
}

BulletManager * BulletManager::create()
{
	BulletManager *pRet = new(std::nothrow) BulletManager();
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

BulletManager * BulletManager::GetInstance()
{
	if (!instance)
	{
		instance = BulletManager::create();
	}
	return instance;
}

bool BulletManager::init()
{
	if (!Node::init())
		return false;
	return true;
}

void BulletManager::Update(float deltaTime)
{
	for (int i = 0; i < listBullet.size(); i++)
	{
		listBullet.at(i)->Update(deltaTime);
	}
}

void BulletManager::Spawn(int _ownerID, Team team, float x, float y, int bulletIndex, eMove dir)
{
	if (bulletIndex < -1)
	{
		auto bullet = GetNewBullet();
		bullet->Spawn(_ownerID, team, x, y, dir);
	}
	else
		listBullet.at(bulletIndex)->Spawn(_ownerID, team, x, y, dir);
}

void BulletManager::HandleShotPackage(BULLET_SPAWN package)
{
	auto bullet = listBullet.at(package.idBullet);
	bullet->Spawn(0, package.team, package.posX, package.posY, package.dir);
}

void BulletManager::HandleDiePackage(BULLET_DIE package)
{
	auto bullet = listBullet.at(package.idBullet);
	bullet->Die();
	bullet->SetPos(package.posX, package.posY);
}

cocos2d::Vector<Bullet*> BulletManager::GetBullets()
{
	return listBullet;
}
