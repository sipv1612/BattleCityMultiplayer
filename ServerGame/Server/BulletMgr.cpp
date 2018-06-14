#include "BulletMgr.h"


BulletMgr* BulletMgr::instance = 0;

BulletMgr::BulletMgr()
{
}

Bullet* BulletMgr::GetIndexBullet()
{
	for (int i = 0; i < listBullet.size(); i++)
	{
		if (listBullet[i]->IsDie())
		{
			return listBullet[i];
		}
	}
	auto bullet = new Bullet();
	bullet->SetID(listBullet.size());
	listBullet.push_back(bullet);
	return bullet;
}


BulletMgr::~BulletMgr()
{
	while (!listBullet.empty())
	{
		delete listBullet.front();
		listBullet.erase(listBullet.begin());
	}
}

BulletMgr * BulletMgr::GetInstance()
{
	if (!instance)
	{
		instance = new BulletMgr();
	}
	return instance;
}

void BulletMgr::Update(float deltaTime)
{
	for (int i = 0; i < listBullet.size(); i++)
	{
		listBullet[i]->Update(deltaTime);
	}
}

void BulletMgr::Spawn(Team team, float x, float y, eMove dir)
{
	auto bullet = GetIndexBullet();
	bullet->Spawn(team, x, y, dir);
}

std::vector<Bullet*> BulletMgr::GetBullets()
{
	return listBullet;
}
