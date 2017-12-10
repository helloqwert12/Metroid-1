#include "RidleyBullet.h"
#include "SoundManager.h"

RidleyBullet::RidleyBullet(int x, int y, bool direction) : BaseObject(RIDLEY_BULLET)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::RIDLEY);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::RIDLEY, "ridley_bullet_01"));
	_sprite->setPosition(x, y);

	_initPosition = GVector2(x, y);

	_animation = new Animation(_sprite, 0.05f);
	_animation->addFrameRect(eID::RIDLEY, "ridley_bullet_01", "ridley_bullet_02", "ridley_bullet_03", "ridley_bullet_04", NULL);

	_effect = SpriteManager::getInstance()->getSprite(eID::BULLET_EFFECT);
	_effect->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BULLET_EFFECT, "explosion_01"));
	_effectAnimation = new Animation(_effect, 0.1);
	_effectAnimation->addFrameRect(BULLET_EFFECT, "explosion_01", "explosion_02", "explosion_03", NULL);

	_hitPoint = 1;
	_isActive = true;

	if (direction)
	{
		_accelerate = GVector2(-50, -600);
		_velocity = GVector2(RIDLEY_BULLET_MOVE_SPEED, 300);
	}
	else
	{
		_sprite->setScaleX(_sprite->getScale().x * (-1));
		_accelerate = GVector2(-50, -600);
		_velocity = GVector2(-RIDLEY_BULLET_MOVE_SPEED, 300);
	}

	Movement* movement = new Movement(_accelerate, _velocity, _sprite);
	_componentList["Movement"] = movement;
}

void RidleyBullet::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;

	_effectStopWatch = new StopWatch();
	_hitStopWatch = new StopWatch();
	_startHitStopWatch = false;
}

void RidleyBullet::update(float deltatime)
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

		// Nếu RidleyBullet ra khỏi khoảng di chuyển thì DESTROY
		if (getDistance(this->getPosition(), _initPosition) > RIDLEY_BULLET_RANGE)
		{
			this->setStatus(eStatus::DESTROY);
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
			SoundManager::getInstance()->play(eSoundID::EXPLOSION_SOUND);

			this->setStatus(DESTROY);
		}
	}
}

void RidleyBullet::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	if (_hitPoint > 0)
		_animation->draw(spriteHandle, viewport);
	else
		_effectAnimation->draw(spriteHandle, viewport);
}

void RidleyBullet::release()
{
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

void RidleyBullet::wasHit(int hitPoint)
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

bool RidleyBullet::isDead()
{
	return (_hitPoint <= 0);
}

void RidleyBullet::active()
{
	_isActive = true;

	auto movement = (Movement*)this->_componentList["Movement"];
	movement->setAccelerate(_accelerate);
	movement->setVelocity(_velocity);
}

void RidleyBullet::deactive()
{
	_isActive = false;

	auto movement = (Movement*)this->_componentList["Movement"];
	movement->setAccelerate(GVector2(0, 0));
	movement->setVelocity(GVector2(0, 0));
}

bool RidleyBullet::isActive()
{
	return _isActive;
}

float RidleyBullet::checkCollision(BaseObject* object, float dt)
{
	if (object->getId() == WALL)
	{
		auto collisionBody = (CollisionBody*)_componentList["CollisionBody"];
		eDirection direction;
		if (collisionBody->checkCollision(object, direction, dt, true))
		{
			// Va chạm Wall thì DESTROY
			this->setStatus(DESTROY);
			return 1.0f;
		}
	}
	return 0;
}
