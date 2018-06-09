#pragma once
#ifndef BULLET_MANAGER
#define BULLET_MANAGER
#include "Bullet.h"

class BulletManager : public Node
{
private:
	cocos2d::Vector<Bullet*> listBullet;
	static BulletManager * instance;

	Bullet* GetNewBullet();
public:
	static BulletManager* create();
	static BulletManager* GetInstance();
	bool init();
	void Update(float deltaTime);
	void Spawn(int _ownerID, Team team, float x, float y, int bulletIndex, eMove dir = eMove::NONE);
	cocos2d::Vector<Bullet*> GetBullets();
};
#endif // !BULLET_MANAGER