#include "Character.h"


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

	this->setObjectSprite(Sprite::create(SPRITE_TANK_BLUE));
	this->SetBoxSize(TANK_BOX_SIZE, TANK_BOX_SIZE);
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

void Character::Update(float deltaTime)
{
	UpdateMove(deltaTime);
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
		moveDir = UP;
		dirShoot = UP;
		this->setRotation(0);
		SetVel(0, SPEED_TANK);
	}
	break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	{
		moveDir = DOWN;
		dirShoot = DOWN;

		this->setRotation(180);
		SetVel(0, -SPEED_TANK);
	}
	break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	{
		moveDir = LEFT;
		dirShoot = LEFT;

		this->setRotation(270);
		SetVel(-SPEED_TANK, 0);
	}
	break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	{
		moveDir = RIGHT;
		dirShoot = RIGHT;

		this->setRotation(90);
		SetVel(SPEED_TANK, 0);
	}
	break;
	case EventKeyboard::KeyCode::KEY_SPACE:
	{
		if (!IsDie() && IsCanShoot())
		{

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

		break;
	}
}


