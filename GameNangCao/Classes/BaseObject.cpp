#include "BaseObject.h"

BaseObject*  BaseObject::create(Team _team)
{
	BaseObject *pRet = new(std::nothrow) BaseObject();
	if (pRet && pRet->init())
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

bool BaseObject::init()
{
	if (!Node::init())
		return false;

	m_sprite = nullptr;
	box = new Box();
	team = Team::None;
	moveDir = eMove::NONE;
	originX = -1;
	originX = -1;
	speedMove = 0;
	ID = 0;
	isDie = false;
	return true;

}

void BaseObject::setObjectSprite(const char* fileName)
{
	if(m_sprite != nullptr)
		this->m_sprite->removeFromParentAndCleanup(true);
	this->m_sprite = Sprite::create(fileName);
	this->addChild(m_sprite);
}

void BaseObject::setObjectSpriteFrame(const char * frameName)
{
	if (m_sprite != nullptr)
		this->m_sprite->removeFromParentAndCleanup(true);
	this->m_sprite = Sprite::createWithSpriteFrameName(frameName);
	this->addChild(m_sprite);
}

void BaseObject::Move(eMove dir)
{
	moveDir = dir;
	switch (moveDir)
	{
	case eMove::UP:
		SetVel(0, -speedMove);
		this->setRotation(0);
		break;
	case eMove::DOWN:
		SetVel(0, speedMove);
		this->setRotation(180);

		break;
	case eMove::LEFT:
		SetVel(-speedMove, 0);
		this->setRotation(270);

		break;
	case eMove::RIGHT:
		SetVel(speedMove, 0);
		this->setRotation(90);

		break;
	default:
		SetVel(0, 0);
		break;
	}
}

void BaseObject::SetSpeed(float speed)
{
	speedMove = speed;
}

void BaseObject::Die()
{
	isDie = true;
	this->setVisible(false);
	//add explosion
	Sprite *explosion = Sprite::create();
	this->getParent()->addChild(explosion);
	explosion->setPosition(this->getPosition());
	Animate *explosionAnimate = getExplosionAnimate();
	auto autoSelfDestroy = CallFuncN::create(
		[&](Node *sender)
	{
		sender->removeFromParentAndCleanup(true);
	});
	explosion->runAction(Sequence::create(explosionAnimate, autoSelfDestroy, nullptr));
}

void BaseObject::Reset()
{
}

void BaseObject::SetID(int id)
{
	ID = id;
}

void BaseObject::Update(float deltaTime)
{

}

void BaseObject::Spawn(Team _team, float _x, float _y, eMove _dir)
{
	SetPos(_x, _y);
	if (originX < 0 || originY < 0)
	{
		originX = _x;
		originY = _y;
	}
	moveDir = _dir;
	team = _team;
	isDie = false;
	this->setVisible(true);
}

void BaseObject::SetPos(float _x, float _y)
{
	box->x = _x;
	box->y = _y;
	this->setPosition(_x, SCREEN_HEIGHT - box->y);
}

void BaseObject::SetVel(float _x, float _y)
{
	box->vx = _x;
	box->vy = _y;
}

void BaseObject::SetBoxSize(int _width, int _height)
{
	box->width = _width;
	box->height = _height;
}

void BaseObject::AABBHandle(float deltaTime, float collisionTime)
{
	box->x += box->vx * collisionTime * deltaTime;
	box->y += box->vy * collisionTime * deltaTime;
	box->vx = 0;
	box->vy = 0;
}

bool BaseObject::IsOutOfScreen()
{
	return (box->x < 0 || box->x + box->width > SCREEN_WIDTH || box->y < 0 || box->y + box->height > SCREEN_HEIGHT);
}

Box*  BaseObject::GetBox()
{
	return box;
}

Team BaseObject::GetTeam()
{
	return team;
}

bool BaseObject::IsDie()
{
	return isDie;
}

void BaseObject::AddDebug(Node* parent)
{
	
	rectNode->drawRect(Vec2(box->x, box->y), Vec2(box->x + box->width, box->y + box->height), Color4F(1.0f, 0.3f, 0.3f, 1));
	parent->addChild(rectNode, 9999);
}

void BaseObject::UpdateDebug()
{
	rectNode->clear();
	rectNode->drawRect(Vec2(box->x, box->y), Vec2(box->x + box->width, box->y + box->height), Color4F(1.0f, 0.3f, 0.3f, 1));
}
