//#ifndef  _PACKET_H_
//#define _PACKET_H_
//
//
//#include <iostream>
//#include <vector>
//#include "Define.h"
//using namespace std;
//
//enum KEY
//{
//	Nothing,
//	TankMove,
//	TankDie,
//	TankRevial,
//	BulletSpawn,
//	BulletDie,
//	TerrainDie
//};
//struct PACKET_KEY
//{
//	KEY key;
//	PACKET_KEY()
//	{
//
//	}
//	PACKET_KEY(KEY _key)
//	{
//		key = _key;
//	}
//}
//;
//struct TANK_MOVE
//{
//	int idTank;
//	float posX;
//	float posY;
//	dMove dir;
//	TANK_MOVE()
//	{
//		idTank = 0;
//		posX = 0;
//		posY = 0;
//		dir = dMove::None;
//	}
//	TANK_MOVE(int id, float x, float y, dMove drc)
//	{
//		idTank = id;
//		posX = x;
//		posY = y;
//		dir = drc;
//	}
//};
//struct TANK_DIE
//{
//	int idTank;
//	TANK_DIE()
//	{
//
//	}
//	TANK_DIE(int id)
//	{
//		idTank = id;
//	}
//};
//struct TANK_REVIVAL
//{
//	int idTank;
//	float posX;
//	float posY;
//	TANK_REVIVAL() 
//	{
//
//	}
//	TANK_REVIVAL(int id, float x, float y)
//	{
//		idTank = id;
//		posX = x;
//		posY = y;
//	}
//};
//struct BULLET_SPAWN
//{
//	int idBullet;
//	float posX;
//	float posY;
//	dMove dir;
//	Team team;
//	BULLET_SPAWN()
//	{
//
//	}
//	BULLET_SPAWN(int id, float x, float y, dMove drc, Team own)
//	{
//		idBullet = id;
//		posX = x;
//		posY = y;
//		dir = drc;
//		team = own;
//	}
//};
//struct BULLET_DIE
//{
//	int idBullet;
//	BULLET_DIE()
//	{
//
//	}
//	BULLET_DIE(int id)
//	{
//		idBullet = id;
//	}
//};
//
//struct TERRAIN_DIE
//{
//	int idTerrain;
//	TERRAIN_DIE()
//	{
//
//	}
//	TERRAIN_DIE(int id)
//	{
//		idTerrain = id;
//	}
//};
//#endif // ! _PACKET_H_