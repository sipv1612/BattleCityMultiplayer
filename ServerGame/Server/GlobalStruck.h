#pragma once
#include "Define.h"
enum eMove
{
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

enum Team 
{
	TEAM_1,
	TEAM_2
};

enum TerrianType 
{ 
	REB,
	SILVER 
};

typedef struct _SOCKET_INFORMATION {
	CHAR buffer[DATA_BUFSIZE];
	WSABUF dataBuf;
	WSABUF dataBufSend;
	SOCKET socket;
	OVERLAPPED Overlapped;
	DWORD bytesSEND;
	DWORD bytesRECV;
} SOCKET_INFORMATION, *LPSOCKET_INFORMATION;

typedef struct
{
	Team Tank;
	eMove Move;
	bool Shooting;
	eMove SideShoot;
	float PosX;
	float PosY;
	bool isDie;
}TANK_STATE;
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
	eMove dir;
	TANK_MOVE(int id, float x, float y, eMove drc)
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
	eMove dir;
	Team team;
	BULLET_SPAWN(int id, float x, float y, eMove drc, Team own)
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
	BULLET_DIE(int id)
	{
		idBullet = id;
	}
};

struct TERRAIN_DIE
{
	int idTerrain;
	TERRAIN_DIE(int id)
	{
		idTerrain = id;
	}
};
typedef struct
{
	int priority;
}Priority;
typedef struct
{
	bool isVisible;
	float PosX;
	float PosY;
	eMove Move;
	Team Own;
}BULLET_STATE;

typedef struct
{
	int ID;
	bool isDie;
	float PosX;
	float PosY;
}BRICK_WORLD;
typedef struct
{
	int teamWin;
	std::vector<BULLET_STATE*> allBullet;
	std::vector<TANK_STATE*> allTank;
	std::vector<BRICK_WORLD*> allBrick;
}UPDATE_WORLD;
