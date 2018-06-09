#pragma once

#include "Character.h"

class TankMgr : public cocos2d::Node
{
private:
	cocos2d::Vector<Tank*> listTank;
	static TankMgr* instance;

	struct Pos
	{
		int x;
		int y;
		Pos(int _x, int _y)
		{
			x = _x;
			y = _y;
		}
	};
	std::vector<Pos> listPosPlayer;
public:

	static TankMgr * create();
	static TankMgr * GetInstance();
	bool init();
	void Update(float deltaTime);
	void Spawn(Team team, float x, float y, eMove dir = NONE, bool isCharactor = false);
	void InitPlayers();
	void HandleMovePackage(TANK_MOVE package);
	void HandleDiePackage(TANK_DIE package);
	void HandleRevivalPackage(TANK_REVIVAL package);
	cocos2d::Vector<Tank*> GetTanks();
	~TankMgr();
	
};


