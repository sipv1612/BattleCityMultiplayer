#include "Tank.h"
#include "BulletMgr.h"
#include "GlobalVariable.h"

Tank::Tank()
{
	SetBoxSize(TANK_SIZE, TANK_SIZE);
	SetSpeed(TANK_SPEED);
}


Tank::~Tank()
{
}


void Tank::Die()
{
	isDie = true;
	Move();
	SendDataDie();
}

void Tank::Reset()
{
}

void Tank::SetRobot()
{
	isRobot = true;
	SetSpeed(ROBOT_SPEED);
}

void Tank::Revival()
{
	timeDie = 0;
	isDie = false;
	Spawn(team, originX, originY);
	SendDataRivival();
}

void Tank::SendDataRivival()
{
	PACKET_KEY key = PACKET_KEY(TankRevial);
	memcpy(dataSendBuffer + LPDataSendBuffer, &key, sizeof PACKET_KEY);
	LPDataSendBuffer += sizeof PACKET_KEY;
	TANK_REVIVAL data = TANK_REVIVAL(iD, originX, originY);
	memcpy(dataSendBuffer + LPDataSendBuffer, &data, sizeof TANK_REVIVAL);
	LPDataSendBuffer += sizeof TANK_REVIVAL;
}

void Tank::SendDataMove()
{
	PACKET_KEY key = PACKET_KEY(TankMove);
	memcpy(dataSendBuffer + LPDataSendBuffer, &key, sizeof PACKET_KEY);
	LPDataSendBuffer += sizeof PACKET_KEY;
	TANK_MOVE data = TANK_MOVE(iD, box->x, box->y, moveDir);
	memcpy(dataSendBuffer + LPDataSendBuffer, &data, sizeof TANK_MOVE);
	LPDataSendBuffer += sizeof TANK_MOVE;
}

void Tank::SendDataShoot()
{
	PACKET_KEY key = PACKET_KEY(BulletSpawn);
	memcpy(dataSendBuffer + LPDataSendBuffer, &key, sizeof PACKET_KEY);
	LPDataSendBuffer += sizeof PACKET_KEY;
	BULLET_SPAWN data = BULLET_SPAWN(iD, box->x, box->y, moveDir, team);
	memcpy(dataSendBuffer + LPDataSendBuffer, &data, sizeof BULLET_SPAWN);
	LPDataSendBuffer += sizeof BULLET_SPAWN;
}

void Tank::SendDataDie()
{
	PACKET_KEY key = PACKET_KEY(TankDie);
	memcpy(dataSendBuffer + LPDataSendBuffer, &key, sizeof PACKET_KEY);
	LPDataSendBuffer += sizeof PACKET_KEY;
	TANK_DIE data = TANK_DIE(iD);
	memcpy(dataSendBuffer + LPDataSendBuffer, &data, sizeof TANK_DIE);
	LPDataSendBuffer += sizeof TANK_DIE;
	//printf("Tank Die \n");
}

bool Tank::IsRobot()
{
	return isRobot;
}

bool Tank::IsCanResurrection()
{
	return timeDie >= TANK_TIME_TO_RESURRECTION;
}

bool Tank::IsPlayerCanShoot()
{
	return timeShoot > TANK_SHOOT_RATE;
}

void Tank::Update(float deltaTime)
{
	UpdateMove(deltaTime);
	UpdateShoot(deltaTime);
	AIRobot(deltaTime);
}

void Tank::UpdateShoot(float deltaTime)
{
	if (IsRobot())
		return;
	timeShoot += deltaTime;
}

void Tank::UpdateMove(float deltaTime)
{
	if (!IsDie())
	{
		if (box->x < 0 || box->x + box->width > SCREEN_WIDTH)
		{
			if (box->x < 0)
				box->x = 0;
			if (box->x + box->width > SCREEN_WIDTH)
				box->x = SCREEN_WIDTH - box->width;
			box->vx = 0;
		}
		if (box->y < 0 || box->y + box->height > SCREEN_HEIGHT)
		{
			if (box->y < 0)
				box->y = 0;
			if (box->y + box->height > SCREEN_HEIGHT)
				box->y = SCREEN_HEIGHT - box->height;
			box->vy = 0;
		}
		box->x += box->vx * deltaTime;
		box->y += box->vy * deltaTime;
		//printf("%f %f \n", box->vx, box->vy);
	}
	else
	{
		timeDie += deltaTime;
	}
	if (IsCanResurrection())
	{
		Revival();
	}
}

void Tank::AIRobot(float deltaTime)
{
	if (isRobot && !IsDie())
	{
		timeAIRobot += deltaTime;
		timeAIShoot += deltaTime;
		
		if (timeAIRobot > ROBOT_TIME_AI)
		{
			int movedir = rand() % 4 + 1;
			switch (movedir)
			{
			case 1:
				Move(UP);
				break;
			case 2:
				Move(DOWN);
				break;
			case 3:
				Move(LEFT);
				break;
			case 4:
				Move(RIGHT);
				break;
			}
			timeAIRobot = 0;
			SendDataMove();
		}
		if (timeAIShoot >= ROBOT_SHOOT_RATE)
		{
			timeAIShoot = 0;
			Shoot();
		}

	}
}

void Tank::Shoot(bool isPlayer)
{
	if (isPlayer && !IsPlayerCanShoot())
		return;
	BulletMgr::GetInstance()->Spawn(team, box->x, box->y, dirShoot);
	SendDataShoot();
}

void Tank::Move(eMove dir)
{
	Object::Move(dir);
	if (moveDir != NONE)
	{
		dirShoot = moveDir;
	}
}


void Tank::Spawn(Team team, float x, float y, eMove dir)
{
	Object::Spawn(team, x, y, dir);
	timeDie = 0;
}
