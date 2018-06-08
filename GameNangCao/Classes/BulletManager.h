#ifndef _BULLET_MANAGER_
#define _BULLET_MANAGER_

#include "Bullet.h"

typedef std::vector<Bullet* > ListBullet;
class BulletManager
{
private:	
	ListBullet bList;
public:

	void Init(std::vector<TANK_STATE*> *_allTank, std::vector<BULLET_STATE*> *_allBullet, std::vector<BRICK*> *_allBrick);
	void Get(Owned type, float x, float y, eMove emove);
	BulletManager();
	~BulletManager();
	void WorldUpdate();
	ListBullet getList();
};
#endif // !_BULLET_MANAGER_