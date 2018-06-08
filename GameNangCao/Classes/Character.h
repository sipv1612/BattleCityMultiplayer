#ifndef _CHARACTER_SCENE_H_
#define _CHARACTER_SCENE_H_
#include "ObjectBase.h"
#include "Packet.h"
#include "Client.h"
#include  "BulletManager.h"
#include <vector>
using namespace std;

class Character : public ObjectBase
{
	cocos2d::Sprite *mTank, *mGun;
	bool isKeyDown = false;
	bool isRun = false;
	bool isReset = true;
	float _TimeFire;
	std::string perfix;
	TANK_STATE UpdateTank;
public:
	TANK_STATE player;
	Character(std::vector<TANK_STATE*> *_allTank, std::vector<BULLET_STATE*> *_allBullet, std::vector<BRICK*> *_allBrick) : ObjectBase(_allTank, _allBullet, _allBrick) {};
	void Init(float x, float y, float speed, eMove emove, int Team);
	bool InitTank(float x, float y, int team);
	bool InitGun(float x, float y, int team);
	void initNet();
	bool InitMouseKeyBoard();
	virtual void update(float delta) override;
	void tankAnimationMove();
	void tankAnimationIdle();
	void followObject();
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	Box* getRecF() {
		return this->CRec;
	}
	void tankMove(float delta);
	void Stop();
	void Reset();
	void Die();
	void UpdateRec();
	cocos2d::Animation * CreateAnimation(std::string perfixName, int pfamesOrder, float delay);
	~Character();
	
};
#endif

