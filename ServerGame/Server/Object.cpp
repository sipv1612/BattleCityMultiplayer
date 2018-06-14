#include "Object.h"

Object::Object()
{
	box = new Box();
	team = Team::TEAM_GREEN;
	moveDir = eMove::NONE;
	originX = 0;
	originX = 0;
	speedMove = 0;
	iD = 0;
	isDie = false;
}


Object::~Object()
{
}

void Object::Init()
{
}

Box * Object::GetBox()
{
	return box;
}

void Object::Move(eMove dir)
{
	moveDir = dir;
	switch (moveDir)
	{
	case eMove::UP:
		SetVel(0, -speedMove);
		break;
	case eMove::DOWN:
		SetVel(0, speedMove);
		break;
	case eMove::LEFT:
		SetVel(-speedMove, 0);
		break;
	case eMove::RIGHT:
		SetVel(speedMove, 0);
		break;
	default:
		SetVel(0, 0);
		break;
	}
}

void Object::SetSpeed(float speed)
{
	speedMove = speed;
}



Team Object::GetTeam()
{
	return team;
}

bool Object::IsDie()
{
	return isDie;
}

void Object::SetOriginPos(float x, float y)
{
	originX = x;
	originY = y;
}

void Object::Die()
{
	isDie = true;

}

void Object::Reset()
{
}

void Object::SetID(int id)
{
	iD = id;
}

void Object::Update(float deltaTime)
{
	
}

void Object::Spawn(Team _team, float _x, float _y, eMove dir)
{
	SetPos(_x, _y);
	moveDir = dir;
	team = _team;
}

void Object::SetPos(float _x, float _y)
{
	box->x = _x;
	box->y = _y;
}

void Object::SetVel(float _x, float _y)
{
	box->vx = _x;
	box->vy = _y;
}

void Object::SetBoxSize(int _width, int _height)
{
	box->width = _width;
	box->height = _height;
}

void Object::AABBHandle(float deltaTime, float collisionTime)
{
	box->x += box->vx * collisionTime * deltaTime;
	box->y += box->vy * collisionTime * deltaTime;
	box->vx = 0;
	box->vy = 0;
}


