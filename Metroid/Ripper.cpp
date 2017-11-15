#include "Ripper.h"

Ripper::Ripper(int x, int y, bool direct) : BaseObject(RIPPER)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::ENEMY);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ENEMY, "y_ripper_01"));
	_sprite->setScale(SCALE_FACTOR);
	_sprite->setPosition(x, y);

	_animation = new Animation(_sprite, 0.2f);
	_animation->addFrameRect(eID::ENEMY, "y_ripper_01", NULL);

	//_effect = SpriteManager::getInstance()->getSprite(eID::EFFECT);
	//_effect->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::EFFECT, "hit_effect_1"));
	//_effectAnimation = new Animation(_effect, 0.15f);
	//_effectAnimation->addFrameRect(EFFECT, "hit_effect_1", "hit_effect_2", "hit_effect_3", NULL);

	_hitPoint = 2;

	auto movement = new Movement(GVector2(0, 0), GVector2(0, 0), _sprite);
	_componentList["Movement"] = movement;

	if (direct)
	{
		_sprite->setScaleX(-1);
		movement->setVelocity(GVector2(RIPPER_MOVE_SPEED, 0));
	}
	else
	{
		movement->setVelocity(GVector2(-RIPPER_MOVE_SPEED, 0));
	}
}

void Ripper::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;

	_effectStopWatch = new StopWatch();
	_hitStopWatch = new StopWatch();
	_startHit = false;
}

void Ripper::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	if (_hitPoint > 0)
		_animation->draw(spriteHandle, viewport);
	else
	{
		_effectAnimation->draw(spriteHandle, viewport);
	}
}

void Ripper::update(float deltatime)
{
	if (_hitPoint > 0)
	{
		_animation->update(deltatime);
		auto move = (Movement*)this->_componentList["Movement"];

		if (_startHit)
		{
			if (_hitStopWatch->isStopWatch(400))
			{
				_startHit = false;
				_hitStopWatch->restart();
			}
		}

		if (_startHit)
		{
			move->setVelocity(GVector2(0, 0));
		}
	}
	else
	{
		//_effect->setPosition(this->getPosition());
		//_effectAnimation->update(deltatime);

		//if (_effectStopWatch->isStopWatch(600))
		//{
		//	this->setStatus(DESTROY);
		//	srand(time(0));
		//	auto ran = rand() % 10;
		//	BaseObject* item = nullptr;
		//	if (ran < 5)
		//		item = new Enegy(this->getPositionX(), this->getPositionY());
		//	if (item != nullptr)
		//	{
		//		item->init();
		//		QuadTreeNode::getInstance()->insert(item);
		//	}
		//}
	}

	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		it->second->update(deltatime);
	}
}

void Ripper::wasHit(int hitpoint)
{
	if (!_startHit)
	{
		_hitPoint -= hitpoint;
		_hitStopWatch->restart();
		_hitStopWatch->isTimeLoop(400);
		_startHit = true;
	}

	if (_hitPoint <= 0)
	{
		auto move = (Movement*)this->_componentList["Movement"];
		move->setVelocity(GVector2(0, 0));
		_effectStopWatch->isTimeLoop(600);
	}
}

float Ripper::checkCollision(BaseObject* object, float dt)
{
	if (object->getId() == WALL)
	{
		auto collisionBody = (CollisionBody*)_componentList["CollisionBody"];
		eDirection direction;
		if (collisionBody->checkCollision(object, direction, dt, false))
		{
			if (direction == LEFT || direction == RIGHT)
			{
				float moveX, moveY;
				if (collisionBody->isColliding(object, moveX, moveY, dt))
				{
					collisionBody->updateTargetPosition(object, direction, false, GVector2(moveX, moveY));
					
					// Đụng tường thì đi ngược lại
					auto movement = (Movement*)this->_componentList["Movement"];
					movement->setVelocity(GVector2(-movement->getVelocity().x, 0));
				}
			}

			return 1.0f;
		}
	}

	return 0;
}

bool Ripper::isDead()
{
	return (_hitPoint <= 0);
}

void Ripper::release()
{
	SAFE_DELETE(_animation);
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}
