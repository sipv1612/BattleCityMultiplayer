#include "Character.h"
#include "BulletManager.h"
#include "GlobalVariable.h"

Character * Character::create(Team _team, bool _isRobot)
{
	Character *pRet = new(std::nothrow) Character();
	if (pRet && pRet->init(_team, _isRobot))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

bool Character::init(Team _team, bool _isRobot)
{
	if (!Tank::init())
		return false;
	
	this->InitMouseKeyBoard();
	this->SetSpeed(SPEED_TANK);
	dirShoot = UP;
	return true;
}

bool Character::InitMouseKeyBoard()
{
	// event keyboard
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(Character::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(Character::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

void Character::SendDataMove()
{
	SEND_KEY key = SEND_KEY(KeySend::Move);
	memcpy(dataSendBuffer + LPDataSendBuffer, &key, sizeof SEND_KEY);
	LPDataSendBuffer += sizeof SEND_KEY;
	SEND_MOVE_DATA data = SEND_MOVE_DATA(ID, moveDir);
	memcpy(dataSendBuffer + LPDataSendBuffer, &data, sizeof SEND_MOVE_DATA);
	LPDataSendBuffer += sizeof SEND_MOVE_DATA;
}

void Character::SendDataShoot()
{
	SEND_KEY key = SEND_KEY(KeySend::Shoot);
	memcpy(dataSendBuffer + LPDataSendBuffer, &key, sizeof SEND_KEY);
	LPDataSendBuffer += sizeof SEND_KEY;
	SEND_SHOOT_DATA data = SEND_SHOOT_DATA(ID, dirShoot);
	memcpy(dataSendBuffer + LPDataSendBuffer, &data, sizeof SEND_SHOOT_DATA);
	LPDataSendBuffer += sizeof SEND_SHOOT_DATA;
}

void Character::Update(float deltaTime)
{
	UpdateMove(deltaTime);
	UpdateShoot(deltaTime);
}

void Character::UpdateShoot(float deltaTime)
{
	timeShoot += deltaTime;
}

bool Character::IsCanShoot()
{
	return timeShoot > PLAYER_TIME_SHOT;
}



Character::~Character()
{
}



void Character::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	{
		dirShoot = UP;
		Move(UP);
		this->setRotation(0);
		SendDataMove();
	}
	break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	{
		dirShoot = DOWN;
		Move(DOWN);
		this->setRotation(180);
		SendDataMove();

	}
	break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	{
		dirShoot = LEFT;
		Move(LEFT);
		this->setRotation(270);
		SendDataMove();

	}
	break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	{
		dirShoot = RIGHT;
		Move(RIGHT);
		this->setRotation(90);
		SendDataMove();

	}
	break;
	case EventKeyboard::KeyCode::KEY_SPACE:
	{
 		if (!IsDie() && IsCanShoot())
		{
			SendDataShoot();
			timeShoot = 0;
		}
	}
	break;
	default:
	{
		
	}
	break;
	}
	
}

void Character::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		Move();
		SendDataMove();

		break;
	}
}


