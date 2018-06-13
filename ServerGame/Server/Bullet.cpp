#include "Bullet.h"
#include "GlobalVariable.h"


Bullet::Bullet()
{
}


Bullet::~Bullet()
{
	delete box;
}

void Bullet::Die()
{
	isDie = true;
	SendDataDie();
}

void Bullet::Reset()
{
}

void Bullet::SendDataDie()
{
	PACKET_KEY key = PACKET_KEY(BulletDie);
	memcpy(dataSendBuffer + LPDataSendBuffer, &key, sizeof PACKET_KEY);
	LPDataSendBuffer += sizeof PACKET_KEY;
	BULLET_DIE data = BULLET_DIE(iD, box->x, box->y);
	memcpy(dataSendBuffer + LPDataSendBuffer, &data, sizeof BULLET_DIE);
	LPDataSendBuffer += sizeof BULLET_DIE;
	//printf("Bullet Die \n");

}

void Bullet::SendDataSpawn()
{
	PACKET_KEY key = PACKET_KEY(BulletSpawn);
	memcpy(dataSendBuffer + LPDataSendBuffer, &key, sizeof PACKET_KEY);
	LPDataSendBuffer += sizeof PACKET_KEY;
	BULLET_SPAWN data = BULLET_SPAWN(iD, box->x, box->y, moveDir, team);
	memcpy(dataSendBuffer + LPDataSendBuffer, &data, sizeof BULLET_SPAWN);
	LPDataSendBuffer += sizeof BULLET_SPAWN;
}

void Bullet::Update(float deltaTime)
{
	UpdateMove(deltaTime);
}

void Bullet::UpdateMove(float deltaTime)
{
	if (!IsDie())
	{
		if (IsOutOfScreen())
		{
			Die();
		}
		box->x += box->vx * deltaTime;
		box->y += box->vy * deltaTime;
	}
	else
	{

	}
}


void Bullet::Spawn(Team _team, float x, float y, eMove dir)
{
	//printf("Bullet Spawn \n");

	team = _team;
	isDie = false;
	SetSpeed(BULLET_SPEED);
	SetPos(x, y);
	Move(dir);
	SendDataSpawn();
	switch (dir)
	{
	case UP:
	case DOWN:
		SetBoxSize(BULLET_WIDTH, BULLET_HEIGHT);
		break;
	case LEFT:
	case RIGHT:
		SetBoxSize(BULLET_WIDTH, BULLET_HEIGHT);
		break;
	default:
		printf("NONEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE\n");
		break;
	}
}


bool Bullet::IsOutOfScreen()
{
	return (box->x < 0 || box->x + box->width > SCREEN_WIDTH || box->y < 0 || box->y + box->height > SCREEN_HEIGHT);
}
