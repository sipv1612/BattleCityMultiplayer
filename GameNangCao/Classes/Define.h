#ifndef __DEFINE_H__
#define __DEFINE_H__


#define SPEED_TANK 100
#define ROBOT_SPEED 70
#define SPEED_BULLET 200
#define SCREEN_HEIGHT 640
#define SCREEN_WIDTH 640
#define OBJECT_MOVE 1
#define CHARACTOR_BITMASK 2
#define TANK_BITMASK 3
#define BRICK_BITMASK 4
#define ROBOT_BITMASK 5
#define BULLET_BITMASK 6
#define OBJECT_STATIC 2

class Box {
public:
	float x, y, vx, vy;
	float width, height;

	Box() {
		x = y = vx = vy = width = height = 0;
	}

	Box(float x, float y, float vx, float vy, int width, int height)
	{
		this->x = x;
		this->y = y;
		this->vx = vx;
		this->vy = vy;
		this->width = width;
		this->height = height;
	}
};
enum eMove
{
	NONE = 0,
	UP = 1,
	LEFT = 2,
	RIGHT = 3,
	DOWN = 4,
	DIE,
	STAY,
	BURST

};

enum eAnimate
{
	STOP,
	RUN
};

enum eStatus
{

};

enum eBullet
{

};

#endif