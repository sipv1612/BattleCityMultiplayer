//#include "Charactor.h"
//
//void Charactor::InitTank()
//{
//	SpriteBatchNode *spriteNode = SpriteBatchNode::create("EnemyMove.png");
//	CCSpriteFrameCache::getInstance()->addSpriteFramesWithFile("EnemyMove.plist");
//	mTank = Sprite::createWithSpriteFrameName("Enemy0.png");
//	addChild(spriteNode);
//	spriteNode->addChild(mTank);
//	mTank->setPosition(100, 100);
//	mTank->setScale(0.25);
//	mTank->setAnchorPoint(Vec2(0.5, 0.5));
//	auto animate = cocos2d::Animate::create(Charactor::CreateAnimation("Enemy", 5, 0.1));
//	animate->retain();
//	mTank->runAction(cocos2d::RepeatForever::create(animate));
//}
//
//void Charactor::InitGun()
//{
//}
//
//cocos2d::Animation * Charactor::CreateAnimation(std::string perfixName, int pfamesOrder, float delay)
//{
//
//	Vector<SpriteFrame*> animFrames;
//	for (int i = 0; i < pfamesOrder; i++)
//	{
//		char buffer[20] = { 0 };
//		sprintf(buffer, "%d.png", i);
//		std::string st = perfixName + buffer;
//		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(st);
//		animFrames.pushBack(frame);
//	}
//	auto animation = Animation::createWithSpriteFrames(animFrames, delay);
//	return animation;
//}
//
//Charactor::Charactor()
//{
//}
//
//Charactor::~Charactor()
//{
//}
//
//void Charactor::Init(float x, float y, float speed, eMove emove)
//{
//	sprite = cocos2d::Sprite::create("up.png", Rect(0, 0, 13, 13));
//	this->addChild(sprite);
//	int check;
//	this->detectSize = 0;
//
//	X = x;
//	Y = y;
//
//	e_Move = emove;
//	e_Animate = eAnimate::RUN;
//
//	Speed = 0;
//
//	timedie = 0;
//
//	auto playerBody = PhysicsBody::createBox(sprite->getContentSize(), PhysicsMaterial(1, 0, 0));
//	playerBody->setContactTestBitmask(1 | 2);
//	playerBody->setCategoryBitmask(1);
//	playerBody->setCollisionBitmask(2);
//	playerBody->setDynamic(true);
//	playerBody->setAngularDamping(0);
//	playerBody->setLinearDamping(0);
//	playerBody->setRotationEnable(false);
//	//playerBody->setVelocity(Vec2(speed, speed));
//
//	this->setPhysicsBody(playerBody);
//	this->setPosition(x, y);
//	//this->scheduleUpdate();
//
//	//Keyboard
//	auto listener = EventListenerKeyboard::create();
//	listener->onKeyPressed = CC_CALLBACK_2(Charactor::onKeyPressed, this);
//	listener->onKeyReleased = CC_CALLBACK_2(Charactor::onKeyReleased, this);
//	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
//}
//
//void Charactor::update(float dt)
//{
//	CCLOG("%f %f", this->getPositionX(), this->getPositionY());
//	if (e_Animate == eAnimate::RUN)
//	{
//		switch (e_Move)
//		{
//		case eMove::UP:
//		{
//
//			//this->setPositionY(this->getPositionY() + Speed * dt);
//			// Y = Y + m_Speed*dt;
//			if (this->detectSize != 4)
//			{
//				this->getPhysicsBody()->setVelocity(Vec2(0, Speed));
//				this->detectSize = 0;
//			}
//
//
//		}
//		break;
//		case eMove::DOWN:
//		{
//			//this->setPositionY(this->getPositionY() - Speed * dt);
//			//Y = Y - m_Speed*dt;
//			if (this->detectSize != 3)
//			{
//				this->getPhysicsBody()->setVelocity(Vec2(0, -(Speed)));
//				this->detectSize = 0;
//			}
//		}
//		break;
//		case eMove::LEFT:
//		{
//			//this->setPositionX(this->getPositionX() - Speed * dt);
//			//X = X - m_Speed*dt;
//			if (this->detectSize != 1)
//			{
//				this->getPhysicsBody()->setVelocity(Vec2(-(Speed), 0));
//				this->detectSize = 0;
//			}
//		}
//		break;
//		case eMove::RIGHT:
//		{
//
//			//this->setPositionX(this->getPositionX() + Speed * dt);
//			// X = X + m_Speed*dt;
//			if (!this->detectSize != 2)
//			{
//				this->getPhysicsBody()->setVelocity(Vec2(Speed, 0));
//				this->detectSize = 0;
//			}
//		}
//		break;
//		case eMove::DIE:
//		{
//			timedie += dt;
//		}
//		break;
//		case eMove::NONE:
//		{
//
//		}
//		break;
//		default:
//			break;
//		}
//	}
//	else
//	{
//		this->getPhysicsBody()->setVelocity(Vec2(0, 0));
//	}
//
//
//	if (e_Animate == eAnimate::RUN || (e_Animate == eAnimate::STOP&&e_Move == eMove::DIE))
//	{
//		sprite->runAction(RepeatForever::create(arrAnimate[e_Move]));
//	}
//	else
//	{
//		//sprite->runAction(RepeatForever::create(arrAnimate[e_Move]));
//		sprite->stopAllActions();
//		sprite->runAction(arrAnimate[e_Move]);
//	}
//
//}
//
//void Charactor::onKeyPressed(EventKeyboard::KeyCode keycode, Event * e)
//{
//	switch (keycode)
//	{
//	case EventKeyboard::KeyCode::KEY_UP_ARROW:
//	{
//		e_Move = UP;
//		e_Animate = eAnimate::RUN;
//		Speed = SPEED_TANK;
//	}
//	break;
//	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
//	{
//		e_Move = DOWN;
//		e_Animate = eAnimate::RUN;
//		Speed = SPEED_TANK;
//	}
//	break;
//	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
//	{
//		e_Move = LEFT;
//		e_Animate = eAnimate::RUN;
//		Speed = SPEED_TANK;
//	}
//	break;
//	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
//	{
//		e_Move = RIGHT;
//		e_Animate = eAnimate::RUN;
//		Speed = SPEED_TANK;
//	}
//	break;
//	case EventKeyboard::KeyCode::KEY_SPACE:
//	{
//		if (e_Move != eMove::DIE)
//		{
//			
//			float x, y;
//			switch (e_Move)
//			{
//			case eMove::UP:
//			{
//				x = getPositionX();
//				y = getPositionY() + 15;
//			}
//			break;
//			case eMove::DOWN:
//			{
//				x = getPositionX();
//				y = getPositionY() - 15;
//			}
//			break;
//			case eMove::LEFT:
//			{
//				x = getPositionX() - 15;
//				y = getPositionY();
//			}
//			break;
//			case eMove::RIGHT:
//			{
//				x = getPositionX() + 15;
//				y = getPositionY();
//			}
//			break;
//			default:
//				break;
//			}
//			ObjectMove* bl = new Bullet();
//			bl->Init(x, y, 50.0f, e_Move);
//			bl->setTag(3);
//			this->addChild(bl);
//		}
//	}
//	break;
//	default:
//	{
//		e_Animate = eAnimate::STOP;
//	}
//	break;
//	}
//}
//
//void Charactor::onKeyReleased(EventKeyboard::KeyCode keycode, Event * e)
//{
//	switch (keycode)
//	{
//	case EventKeyboard::KeyCode::KEY_UP_ARROW:
//	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
//	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
//	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
//	{
//		e_Animate = eAnimate::STOP;
//		Speed = 0;
//	}
//	break;
//	default:
//		break;
//	}
//}
