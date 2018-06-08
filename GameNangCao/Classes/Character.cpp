#include "Character.h"


#define PI 3.141592654
extern bool RecvedData;

void Character::Init(float x, float y, float speed, eMove emove, int Team)
{
	InitTank(x, y, Team);
	InitGun(x,y, Team);
	InitMouseKeyBoard();
#pragma region packet
	
	player.Move = NONE;
	player.PosX = mTank->getPositionX();
	player.PosY = mTank->getPositionY();
	player.Shooting = false;
	player.SideShoot = NONE;
	e_Move = emove;
	allTank->push_back(&UpdateTank);
#pragma endregion

	mTank->setPosition(x, y);
	_TimeFire = 0;
	
	CRec = new Box(x, y, 0, 0, 30, 30);

}

bool Character::InitTank(float x, float y, int team)
{
	if (team == 1)
	{
		SpriteBatchNode *spriteNode = SpriteBatchNode::create("EnemyMove.png");
		CCSpriteFrameCache::getInstance()->addSpriteFramesWithFile("EnemyMove.plist");
		mTank = Sprite::createWithSpriteFrameName("Enemy0.png");
		addChild(spriteNode);
		spriteNode->addChild(mTank);
		auto animate = cocos2d::Animate::create(Character::CreateAnimation("Enemy", 5, 0.1));
		animate->retain();
		mTank->runAction(cocos2d::RepeatForever::create(animate));
		perfix = "Enemy";
		player.Tank = Owned::TEAM_1;
	}
	if (team == 2)
	{
		SpriteBatchNode *spriteNode = SpriteBatchNode::create("RedTank.png");
		CCSpriteFrameCache::getInstance()->addSpriteFramesWithFile("RedTank.plist");
		mTank = Sprite::createWithSpriteFrameName("Tank0.png");
		addChild(spriteNode);
		spriteNode->addChild(mTank);
		auto animate = cocos2d::Animate::create(Character::CreateAnimation("Tank", 5, 0.1));
		animate->retain();
		mTank->runAction(cocos2d::RepeatForever::create(animate));
		perfix = "Tank";
		player.Tank = Owned::TEAM_2;
	}
	mTank->setPosition(x, y);
	mTank->setScale(0.15);
	mTank->setAnchorPoint(Vec2(0.5, 0.5));		
	return true;
}

bool Character::InitGun(float x, float y, int team)
{
	if (team == 1)
		mGun = Sprite::create("EnemyGun.png");
	if (team == 2)
		mGun = Sprite::create("RedGun.png");
	mGun->setPosition(x, y);
	mGun->setAnchorPoint(Vec2(0.5f, 0.231f));
	mGun->setScale(0.15);
	addChild(mGun, 0);
	return true;
}

void Character::initNet()
{
	
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

void Character::update(float delta)
{
	
	//mTank->setPosition(mTank->getPositionX() + veloc.x*delta, mTank->getPositionY() + veloc.y*delta);
	if (UpdateTank.isDie == 1)
		Die();
	else
	{
		if (isRun)
		{
			if (isKeyDown == false)
				tankAnimationMove();
			tankMove(delta);
		}
		else
		{
			if (isKeyDown)
				tankAnimationIdle();
			mTank->setPosition(Vec2(UpdateTank.PosX, UpdateTank.PosY));
		}
		if (isReset == false)
			Reset();
		if (UpdateTank.Move == UP || UpdateTank.Move == DOWN || UpdateTank.Move == RIGHT || UpdateTank.Move == LEFT)
			isRun = true;
		else
			isRun = false;
	}
	player.PosX = mTank->getPositionX();
	player.PosY = mTank->getPositionY();
	_TimeFire += delta;
	followObject();
}

void Character::tankAnimationMove()
{
	mTank->stopAllActions();
	auto animate = cocos2d::Animate::create(Character::CreateAnimation(perfix, 5, 0.1));
	animate->retain();
	mTank->runAction(cocos2d::RepeatForever::create(animate));
	isKeyDown = true;
	
}

void Character::tankAnimationIdle()
{
	mTank->stopAllActions();
	auto animate = cocos2d::Animate::create(Character::CreateAnimation(perfix, 1, 0.1));
	animate->retain();
	mTank->runAction(animate);
	isKeyDown = false;
}

Character::~Character()
{
}

void Character::followObject()
{
	this->mGun->setPosition(mTank->getPosition());
}

void Character::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	{
		e_Move = UP;
		mTank->setRotation(0);
		mGun->setRotation(0);
		veloc.y = SPEED_TANK;
		veloc.x = 0;
		player.Move = e_Move;
	}
	break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	{
		e_Move = DOWN;	
		mTank->setRotation(180);
		mGun->setRotation(180);
		veloc.y = -SPEED_TANK;
		veloc.x = 0;
		player.Move = e_Move;
	}
	break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	{
		e_Move = LEFT;	
		
		veloc.x = -SPEED_TANK;
		veloc.y = 0;
		mTank->setRotation(270);
		mGun->setRotation(270);
		player.Move = e_Move;
	}
	break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	{
		e_Move = RIGHT;	
		
		veloc.x = SPEED_TANK;
		veloc.y = 0;
		mTank->setRotation(90);
		mGun->setRotation(90);
		player.Move = e_Move;
	}
	break;
	case EventKeyboard::KeyCode::KEY_SPACE:
	{
		if (e_Move != eMove::DIE && _TimeFire > 2)
		{		
			switch (e_Move)
			{
			case eMove::UP:
			{
				player.Shooting = true;
				player.SideShoot = UP;
			}
			break;
			case eMove::DOWN:
			{
				
				player.Shooting = true;
				player.SideShoot = DOWN;
			}
			break;
			case eMove::LEFT:
			{
				
				player.Shooting = true;
				player.SideShoot = LEFT;
			}
			break;
			case eMove::RIGHT:
			{
				player.Shooting = true;
				player.SideShoot = RIGHT;
			}
			break;
			default:
				break;
			}
			
			_TimeFire = 0;
			
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
		player.Move = NONE;
		veloc = Vec2(0, 0);
		break;
	}
}

void Character::Reset()
{
	mTank->setVisible(true);
	mGun->setVisible(true);
	isReset = true;
	mTank->setPosition(UpdateTank.PosX, UpdateTank.PosY);
}

void Character::tankMove(float delta)
{
	switch (UpdateTank.Move)
	{
	case eMove::UP:
	{

		mTank->setPosition(mTank->getPositionX(), mTank->getPositionY() + SPEED_TANK*delta);	
		mTank->setRotation(0);
		mGun->setRotation(0);
		if (mTank->getPositionY() > UpdateTank.PosY)
			mTank->setPositionY(UpdateTank.PosY);
	}
	break;
	case eMove::DOWN:
	{

		mTank->setPosition(mTank->getPositionX(), mTank->getPositionY() - SPEED_TANK*delta);
		mTank->setRotation(180);
		mGun->setRotation(180);
		if (mTank->getPositionY() < UpdateTank.PosY)
			mTank->setPositionY(UpdateTank.PosY);
	}
	break;
	case eMove::LEFT:
	{

		mTank->setPosition(mTank->getPositionX() - SPEED_TANK*delta, mTank->getPositionY());
		mTank->setRotation(270);
		mGun->setRotation(270);
		if (mTank->getPositionX() < UpdateTank.PosX)
			mTank->setPositionX(UpdateTank.PosX);
	}
	break;
	case eMove::RIGHT:
	{

		mTank->setPosition(mTank->getPositionX() + SPEED_TANK*delta, mTank->getPositionY());
		mTank->setRotation(90);
		mGun->setRotation(90);
		if (mTank->getPositionX() > UpdateTank.PosX)
			mTank->setPositionX(UpdateTank.PosX);
	}
	break;
	case eMove::DIE:
	{

	}
	break;
	case eMove::NONE:
	{

	}
	break;
	default:
		break;
	}
}

void Character::Stop()
{
	veloc.x = 0;
	veloc.y = 0;
}

void Character::Die()
{
	mTank->setVisible(false);
	mGun->setVisible(false);
	if (isReset)
	{
		TBurst* tb = new TBurst();
		tb->init(mTank->getPositionX(), mTank->getPositionY());
		addChild(tb);
	}
	isReset = false;
}

void Character::UpdateRec()
{
	this->CRec->vx = veloc.x;
	this->CRec->vy = veloc.y;
	this->CRec->x = mTank->getPositionX();
	this->CRec->y = mTank->getPositionY();
}

cocos2d::Animation * Character::CreateAnimation(std::string perfixName, int pfamesOrder, float delay)
{
	Vector<SpriteFrame*> animFrames;
	for (int i = 0; i < pfamesOrder; i++)
	{
		char buffer[20] = { 0 };
		sprintf(buffer, "%d.png", i);
		std::string st = perfixName + buffer;
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(st);
		animFrames.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(animFrames, delay);
	return animation;
}




