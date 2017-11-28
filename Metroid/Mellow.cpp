#include "Mellow.h"

Mellow::Mellow(int x, int y, bool direction) : BaseObject(MELLOW)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::ENEMY);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ENEMY, "mellow_01"));
	_sprite->setPosition(x, y);

	_animation = new Animation(_sprite, 0.1f);
	_animation->addFrameRect(eID::ENEMY, "mellow_01", "mellow_02", NULL);

	_effect = SpriteManager::getInstance()->getSprite(eID::BULLET_EFFECT);
	_effect->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BULLET_EFFECT, "explosion_01"));
	_effectAnimation = new Animation(_effect, 0.1);
	_effectAnimation->addFrameRect(BULLET_EFFECT, "explosion_01", "explosion_02", "explosion_03", NULL);

	_hitPoint = 2;
	_isActive = false;

	auto movement = new Movement(GVector2(0, 0), GVector2(0, 0), _sprite);
	_componentList["Movement"] = movement;

	if (!direction)
	{
		_sprite->setScaleX(_sprite->getScale().x * (-1));
	}
}

void Mellow::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;

	_effectStopWatch = new StopWatch();
	_hitStopWatch = new StopWatch();
	_startHitStopWatch = false;
}

void Mellow::update(float deltatime)
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
				// Do đã có điều kiện active bên Player nên không cần active lại
				//this->active();
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
		}
	}
}

void Mellow::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	if (_hitPoint > 0)
		_animation->draw(spriteHandle, viewport);
	else
		_effectAnimation->draw(spriteHandle, viewport);
}

void Mellow::release()
{
	SAFE_DELETE(_animation);
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

void Mellow::wasHit(int hitPoint)
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

bool Mellow::isDead()
{
	return (_hitPoint <= 0);
}

void Mellow::active(bool direction)
{
	_isActive = true;

	auto movement = (Movement*)this->_componentList["Movement"];
	if (direction)
	{
		movement->setVelocity(GVector2(MELLOW_MOVE_SPEED, -250));
	}
	else
	{
		_sprite->setScaleX(_sprite->getScale().x * -1);
		movement->setVelocity(GVector2(-MELLOW_MOVE_SPEED, -250));
	}
}

void Mellow::deactive()
{
	_isActive = false;

	auto movement = (Movement*)this->_componentList["Movement"];
	movement->setVelocity(GVector2(0, 0));
}

bool Mellow::isActive()
{
	return _isActive;
}

float Mellow::checkCollision(BaseObject* object, float dt)
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

				// Va chạm Wall TOP hoặc BOTTOM thì đi chéo ngược lại
				if (direction == TOP || direction == BOTTOM)
				{
					auto movement = (Movement*)this->_componentList["Movement"];
					movement->setVelocity(GVector2(movement->getVelocity().x, -movement->getVelocity().y));
					this->setScaleX(this->getScale().x * -1);
				}
			}
			return 1.0f;
		}
	}
	return 0;
}
