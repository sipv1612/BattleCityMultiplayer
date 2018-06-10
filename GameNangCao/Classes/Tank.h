#pragma once

#include <vector>
#include "BaseObject.h"

using namespace std;

class Tank : public BaseObject
{
protected:
	bool isRobot = false;
public:
	static Tank * create(Team _team = Team::TeamBlue, bool isRobot = false);
	bool init(Team _team = Team::TeamBlue, bool isRobot = false);

	bool IsRobot();
	void Spawn(Team _team, float _x, float _y, eMove _dir = NONE) override;
	void Revival();
	void Reset();
	void SetRobot();
	void Shoot(bool isPlayer = false);
	void UpdateMove(float deltaTime);
	void Update(float deltaTime);
	~Tank();
	
};

