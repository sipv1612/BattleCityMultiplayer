#ifndef __DEFINE_H__
#define __DEFINE_H__

#include "cocos2d.h"
#include "Box.h"

USING_NS_CC;

#define SPEED_TANK 100
#define SPEED_ROBOT 70
#define SPEED_BULLET 200
#define SCREEN_WIDTH 768
#define SCREEN_HEIGHT 704
#define TANK_BOX_SIZE 28
#define PLAYER_TIME_SHOT 1
#define BULLET_BOX_WIDTH 2.8125
#define BULLET_BOX_HEIGHT 3.75

#define MAP_WIDTH 25
#define MAP_HEIGHT 23
#define MAP_TILED_SIZE 32
#define MAP_TERRAIN_RED 1
#define MAP_TERRAIN_SLIVER 3
#define MAP_TANK_TEAM_1 5
#define MAP_TANK_TEAM_2 4
#define MAP_BIRTH_TEAM_1 6
#define MAP_BIRTH_TEAM_2 2

#define DEFAULT_COUNT       2
#define DEFAULT_PORT        5150
#define DEFAULT_BUFFER      5000
#define BUFFER_SIZE			20480
#define DATA_BUFFER			8192

enum ObjectType
{
	TypeBrick,
	TypeConcrete,
	TypeTank,
	TypeBullet,
	TypeCommandBase,
	TypeItem,
	TypeNone
};

enum TerrainType
{
	BRICK,
	CONCRETE
};

enum Team
{
	TeamGreen,
	TeamBlue,
	None
};

enum eMove
{
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

enum KEY
{
	TankMove,
	TankDie,
	TankRevial,
	BulletSpawn,
	BulletDie,
	TerrainDie,
	Nothing
};

struct PACKET_KEY
{
	KEY key;
	PACKET_KEY(KEY _key)
	{
		key = _key;
	}
};

struct TANK_MOVE
{
	int idTank;
	float posX;
	float posY;
	eMove dir;
	TANK_MOVE()
	{

	}
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
	float posX;
	float posY;
	TANK_DIE() {}
	TANK_DIE(int id, float x, float y)
	{
		idTank = id;
		posX = x;
		posY = y;
	}
};
struct TANK_REVIVAL
{
	int idTank;
	float posX;
	float posY;
	TANK_REVIVAL() {}
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
	BULLET_SPAWN() {}
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
	float posX;
	float posY;
	BULLET_DIE() {}
	BULLET_DIE(int id, float x, float y)
	{
		idBullet = id;
		posX = x;
		posY = y;
	}
};

struct TERRAIN_DIE
{
	int idTerrain;
	TERRAIN_DIE() {}
	TERRAIN_DIE(int id)
	{
		idTerrain = id;
	}
};

enum KeySend
{
	Move,
	Shoot
};
struct SEND_KEY
{
	KeySend key;
	SEND_KEY(KeySend _key)
	{
		key = _key;
	}
};
struct SEND_MOVE_DATA
{
	int iD;
	eMove dir;
	SEND_MOVE_DATA(int _iD, eMove _dir)
	{
		iD = _iD;
		dir = _dir;
	}
};
struct SEND_SHOOT_DATA
{
	int iD;
	eMove dirShot;
	SEND_SHOOT_DATA(int _iD, eMove _dir)
	{
		iD = _iD;
		dirShot = _dir;
	}
};
 
#pragma region Assets
static const cocos2d::Size SIZE_BRICK = cocos2d::Size(32, 32);
static const cocos2d::Size SIZE_CONCRETE = cocos2d::Size(32, 32);
static const cocos2d::Size SIZE_COMMAND_BASE = cocos2d::Size(32, 32);
static const cocos2d::Size SIZE_BULLET = cocos2d::Size(16, 16);
static const cocos2d::Size SIZE_TANK = cocos2d::Size(198, 203);
static const float MAX_HEALTH_BRICK = 3;

static const char* SPRITE_BRICK = "Brick.png";
static const char* SPRITE_CONCRETE = "Concrete.png";
static const char* SPRITE_COMMAND_BASE = "CommandBase.png";
static const char* SPRITE_BULLET = "EnemyBullet.png";
static const char* SPRITE_TANK_RED = "RedTank.png";
static const char* SPRITE_TANK_BLUE = "BlueTeam.png";
static const char* SPRITE_TANK_GREEN = "GreenTeam.png";
static const char* SPRITE_EXPLOSION = "tburst.png";
static const char* SPRITE_EXPLOSION_CHILD = "TBurst_%d.png";
static const char* SPRITE_TANK_RED_CHILD = "RedTank%d.png";
static const char* SPRITE_TANK_BLUE_CHILD = "BlueTeam%d.png";
static const char* SPRITE_TANK_GREEN_CHILD = "GreenTeam%d.png";

//----------------------------------

static const char* PLIST_EXPLOSION = "tburst.plist";
static const char* PLIST_TANK_RED = "RedTank.plist";
static const char* PLIST_TANK_BLUE = "BlueTeam.plist";
static const char* PLIST_TANK_GREEN = "GreenTeam.plist";
#pragma endregion

#pragma region FUNCTIONS
inline void loadCaches()
{
	cocos2d::SpriteFrameCache *cache = cocos2d::SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile(PLIST_EXPLOSION, SPRITE_EXPLOSION);
	cache->addSpriteFramesWithFile(PLIST_TANK_RED, SPRITE_TANK_RED);
	cache->addSpriteFramesWithFile(PLIST_TANK_BLUE, SPRITE_TANK_BLUE);
	cache->addSpriteFramesWithFile(PLIST_TANK_GREEN, SPRITE_TANK_GREEN);
}

inline cocos2d::Animate* getExplosionAnimate()
{
	cocos2d::SpriteFrameCache *cache = cocos2d::SpriteFrameCache::getInstance();
	//create animate
	cocos2d::Vector<cocos2d::SpriteFrame*> animFrames(5);
	char str[20] = { 0 };
	for (int i = 0; i < 5; i++) {
		sprintf(str, SPRITE_EXPLOSION_CHILD, i);
		cocos2d::SpriteFrame* frame = cache->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}
	auto animation = cocos2d::Animation::createWithSpriteFrames(animFrames, 0.05f);
	auto animate = cocos2d::Animate::create(animation);
	return animate;
}

inline cocos2d::Animate* getTankMoveAnimate(Team team, bool isBot = false)
{
	cocos2d::SpriteFrameCache *cache = cocos2d::SpriteFrameCache::getInstance();
	//create animate
	cocos2d::Vector<cocos2d::SpriteFrame*> animFrames;
	char str[20] = { 0 };
	switch (team)
	{
	case TeamBlue:
		for (int i = 0; i < 8; i++) {
			sprintf(str, SPRITE_TANK_BLUE_CHILD, i);
			cocos2d::SpriteFrame* frame = cache->getSpriteFrameByName(str);
			animFrames.pushBack(frame);
		}
		break;
	case TeamGreen:
		for (int i = 0; i < 8; i++) {
			sprintf(str, SPRITE_TANK_GREEN_CHILD, i);
			cocos2d::SpriteFrame* frame = cache->getSpriteFrameByName(str);
			animFrames.pushBack(frame);
		}
		break;
	default:
		break;
	}
	auto animation = cocos2d::Animation::createWithSpriteFrames(animFrames, 0.05f);
	auto animate = cocos2d::Animate::create(animation);
	return animate;
}
#pragma endregion

#endif