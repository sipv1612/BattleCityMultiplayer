#pragma once
#include "Define.h"
#include "Tank.h"
class TankMgr
{
private:
	std::vector<Tank*> listTank;
	static TankMgr* instance;
	TankMgr();

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
	static TankMgr* GetInstance();
	void Update(float deltaTime);
	void Packing();
	void SpawnPlayer();
	void SpawnRobot(Team team, float x, float y);
	std::vector<Tank*> GetTanks();
	~TankMgr();
};

