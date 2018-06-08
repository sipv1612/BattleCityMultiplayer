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


#endif // ! _PACKET_H_