#ifndef _CHARACTER_SCENE_H_
#define _CHARACTER_SCENE_H_

#include "Tank.h"

class Character : public Tank
{
	bool isKeyDown = false;
	float timeShoot = 0;
	eMove dirShoot = NONE;
	std::string perfix;
public:

	static Character * create(Team _team = Team::TeamBlue, bool isRobot = false);
	bool init(Team _team = Team::TeamBlue, bool isRobot = false);
	void Update(float deltaTime);
	void UpdateShoot(float deltaTime);
	bool IsCanShoot();
	bool InitMouseKeyBoard();
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	
	~Character();
	
};
#endif

