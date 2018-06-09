#ifndef  _PACKET_H_
#define _PACKET_H_


#include <iostream>
#include <vector>
#include "Define.h"
using namespace std;

enum Mess
{
	OK,
	FAILED,
	WORLD,
	LOGIN,
	STATE
};


enum Owned {
	TEAM_1,
	TEAM_2
};

typedef struct 
{
	char PlayerName[20];
} LOGIN_PLAYER;

typedef struct
{
	vector<LOGIN_PLAYER> allPlayer;
}MULTI_PLAYER;
typedef struct
{
	Owned Tank;
	eMove Move;
	bool Shooting;
	eMove SideShoot;
	float PosX;
	float PosY;
	bool isDie;
}TANK_STATE;

typedef struct
{
	int ID;
	bool IsVisible;
	float PosX;
	float PosY;
	eMove Move;
	Owned Own;
}BULLET_STATE;
typedef struct
{
	int ID;
	bool isDie;
	float PosX;
	float PosY;
}BRICK;
typedef struct
{
	vector<TANK_STATE*> allPlayer;
	vector<BRICK*> allBrick;
	vector<BULLET_STATE*> allBullet;
}UPDATE_WORLD;



enum Team
{
	TEAM_1a,
	TEAM_2b
};

enum TerrianType
{
	REB,
	SILVER
};
enum dMove
{
	None,
	Up,
	Down,
	Left,
	Right
};
enum KEY
{
	Nothing,
	TankMove,
	TankDie,
	TankRevial,
	BulletSpawn,
	BulletDie,
	TerrainDie
};
struct PACKET_KEY
{
	KEY key;
	PACKET_KEY()
	{

	}
	PACKET_KEY(KEY _key)
	{
		key = _key;
	}
}
;
struct TANK_MOVE
{
	int idTank;
	float posX;
	float posY;
	dMove dir;
	TANK_MOVE()
	{
		idTank = 0;
		posX = 0;
		posY = 0;
		dir = dMove::None;
	}
	TANK_MOVE(int id, float x, float y, dMove drc)
	{
		idTank = id;
		posX = x;
		posY = y;
		dir = drc;
	}
};
struct TANK_DIE
{
	int idTank;
	TANK_DIE()
	{

	}
	TANK_DIE(int id)
	{
		idTank = id;
	}
};
struct TANK_REVIVAL
{
	int idTank;
	float posX;
	float posY;
	TANK_REVIVAL() 
	{

	}
	TANK_REVIVAL(int id, float x, float y)
	{
		idTank = id;
		posX = x;
		posY = y;
	}
};
struct BULLET_SPAWN
{
	int idBullet;
	float posX;
	float posY;
	dMove dir;
	Team team;
	BULLET_SPAWN()
	{

	}
	BULLET_SPAWN(int id, float x, float y, dMove drc, Team own)
	{
		idBullet = id;
		posX = x;
		posY = y;
		dir = drc;
		team = own;
	}
};
struct BULLET_DIE
{
	int idBullet;
	BULLET_DIE()
	{

	}
	BULLET_DIE(int id)
	{
		idBullet = id;
	}
};

struct TERRAIN_DIE
{
	int idTerrain;
	TERRAIN_DIE()
	{

	}
	TERRAIN_DIE(int id)
	{
		idTerrain = id;
	}
};
#endif // ! _PACKET_H_