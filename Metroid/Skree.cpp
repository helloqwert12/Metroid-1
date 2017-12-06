#include "Skree.h"

Skree::Skree(int x, int y) : BaseObject(SKREE)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::ENEMY);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ENEMY, "yellow_skree_01"));
	_sprite->setPosition(x, y);

	_animation = new Animation(_sprite, 0.07f);
	_animation->addFrameRect(eID::ENEMY, "yellow_skree_01", "yellow_skree_02", NULL);

	_effect = SpriteManager::getInstance()->getSprite(eID::BULLET_EFFECT);
	_effect->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BULLET_EFFECT, "explosion_01"));
	_effectAnimation = new Animation(_effect, 0.1);
	_effectAnimation->addFrameRect(BULLET_EFFECT, "explosion_01", "explosion_02", "explosion_03", NULL);
	
	_hitPoint = 2;
	_isActive = false;
	_shootBullet = false;

	auto movement = new Movement(GVector2(0, 0), GVector2(0, 0), _sprite);
	_componentList["Movement"] = movement;
}

void Skree::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;

	_effectStopWatch = new StopWatch();
	_hitStopWatch = new StopWatch();
	_startHitStopWatch = false;
}

void Skree::update(float deltatime)
{
	if (_hitPoint > 0)
	{
		_animation->update(deltatime);

		if (_startHitStopWatch)
		{
			// Nếu đang trong thời gian protect thì deactive
			this->deactive();

			// Check để sau khi hết khoảng thời gian protect thì tắt hitStopWatch
			// Active lại
			if (_hitStopWatch->isStopWatch(400))
			{
				_startHitStopWatch = false;
				_hitStopWatch->restart();
				this->active();
			}
		}

		for (auto it = _componentList.begin(); it != _componentList.end(); it++)
		{
			it->second->update(deltatime);
		}
	}
	else
	{
		_effect->setPosition(this->getPosition());
		_effectAnimation->update(deltatime);

		if (_effectStopWatch->isStopWatch(200))
		{
			this->setStatus(DESTROY);

			BaseObject* item = nullptr;

			srand(time(0));
			auto random = rand() % 10;
			if (random < 5)
				item = new EnergyBall(this->getPositionX(), this->getPositionY());
			if (item != nullptr)
			{
				item->init();
				QuadTreeNode::getInstance()->insert(item);
			}

			if (_shootBullet)
			{
				item = new SkreeBullet(this->getPositionX(), this->getPositionY(), GVector2(-SKREE_BULLET_MOVE_SPEED, 0));
				item->init();
				QuadTreeNode::getInstance()->insert(item);

				item = new SkreeBullet(this->getPositionX(), this->getPositionY(), GVector2(SKREE_BULLET_MOVE_SPEED, 0));
				item->init();
				QuadTreeNode::getInstance()->insert(item);

				item = new SkreeBullet(this->getPositionX(), this->getPositionY(), GVector2(-SKREE_BULLET_MOVE_SPEED, 175));
				item->init();
				QuadTreeNode::getInstance()->insert(item);

				item = new SkreeBullet(this->getPositionX(), this->getPositionY(), GVector2(SKREE_BULLET_MOVE_SPEED, 175));
				item->init();
				QuadTreeNode::getInstance()->insert(item);
			}
		}
	}
}

void Skree::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	if (_hitPoint > 0)
		_animation->draw(spriteHandle, viewport);
	else
		_effectAnimation->draw(spriteHandle, viewport);
}

void Skree::release()
{
	SAFE_DELETE(_animation);
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

void Skree::wasHit(int hitPoint)
{
	// Nếu không trong khoảng thời gian protect thì trừ HP và bật hitStopWatch
	// Nếu đang trong khoảng thời gian protect thì không trừ HP
	if (!_startHitStopWatch)
	{
		_hitPoint -= hitPoint;
		_hitStopWatch->restart();
		_startHitStopWatch = true;
	}

	if (_hitPoint <= 0)
	{
		auto move = (Movement*)this->_componentList["Movement"];
		move->setVelocity(GVector2(0, 0));
	}
}

bool Skree::isDead()
{
	return (_hitPoint <= 0);
}

void Skree::active()
{
	_isActive = true;

	auto sinMovement = new SinMovement(GVector2(30, 0), 0.5, _sprite);
	this->_componentList["SinMovement"] = sinMovement;

	auto movement = (Movement*)this->_componentList["Movement"];
	movement->setVelocity(GVector2(0, -SKREE_MOVE_SPEED));
}

void Skree::deactive()
{
	_isActive = false;

	auto movement = (Movement*)this->_componentList["Movement"];
	movement->setVelocity(GVector2(0, 0));

	auto sinMovement = (Movement*)this->_componentList["SinMovement"];
	_componentList.erase("SinMovement");
	delete sinMovement;
}

bool Skree::isActive()
{
	return _isActive;
}

float Skree::checkCollision(BaseObject* object, float dt)
{
	if (object->getId() == WALL)
	{
		auto collisionBody = (CollisionBody*)_componentList["CollisionBody"];
		eDirection direction;
		if (collisionBody->checkCollision(object, direction, dt, false))
		{
			float moveX, moveY;
			if (collisionBody->isColliding(object, moveX, moveY, dt))
			{
				// Update lại vị trí (tránh không cho đi xuyên)
				collisionBody->updateTargetPosition(object, direction, false, GVector2(moveX, moveY));

				// Va chạm Wall TOP thì chết
				if (direction == TOP)
				{
					this->wasHit(2);
					_shootBullet = true;
				}
			}
			return 1.0f;
		}
	}
	return 0;
}
