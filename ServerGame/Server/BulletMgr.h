#pragma once
#include "Bullet.h"
class BulletMgr
{
private:
	std::vector<Bullet*> listBullet;
	static BulletMgr * instance;
	BulletMgr();

	Bullet* GetIndexBullet();
public:
	~BulletMgr();
	static BulletMgr* GetInstance();
	void Update(float deltaTime);
	void Spawn(Team team, float x, float y, eMove dir = NONE);
	std::vector<Bullet*> GetBullets();
};

