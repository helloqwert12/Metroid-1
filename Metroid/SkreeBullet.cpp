#include "SkreeBullet.h"

SkreeBullet::SkreeBullet(int x, int y, GVector2 velocity) : BaseObject(SKREE_BULLET)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::ENEMY);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ENEMY, "skree_bullet_01"));
	_sprite->setPosition(x, y);

	_initPosition = GVector2(x, y);

	_effect = SpriteManager::getInstance()->getSprite(eID::BULLET_EFFECT);
	_effect->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BULLET_EFFECT, "explosion_01"));
	_effectAnimation = new Animation(_effect, 0.1);
	_effectAnimation->addFrameRect(BULLET_EFFECT, "explosion_01", "explosion_02", "explosion_03", NULL);

	_hitPoint = 1;
	_isActive = true;
	_velocity = velocity;

	auto movement = new Movement(GVector2(0, 0), _velocity, _sprite);
	_componentList["Movement"] = movement;
}

void SkreeBullet::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;

	_effectStopWatch = new StopWatch();
	_hitStopWatch = new StopWatch();
	_startHitStopWatch = false;
}

void SkreeBullet::update(float deltatime)
{
	if (_hitPoint > 0)
	{
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

		// Nếu SkreeBullet ra khỏi khoảng di chuyển thì DESTROY
		if (getDistance(this->getPosition(), _initPosition) > SKREE_BULLET_RANGE)
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
			this->setStatus(DESTROY);
		}
	}
}

void SkreeBullet::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	if (_hitPoint > 0)
		_sprite->render(spriteHandle, viewport);
	else
		_effectAnimation->draw(spriteHandle, viewport);
}

void SkreeBullet::release()
{
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

void SkreeBullet::wasHit(int hitPoint)
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

bool SkreeBullet::isDead()
{
	return (_hitPoint <= 0);
}

void SkreeBullet::active()
{
	_isActive = true;

	auto movement = (Movement*)this->_componentList["Movement"];
	movement->setVelocity(_velocity);
}

void SkreeBullet::deactive()
{
	_isActive = false;

	auto movement = (Movement*)this->_componentList["Movement"];
	movement->setVelocity(GVector2(0, 0));
}

bool SkreeBullet::isActive()
{
	return _isActive;
}

float SkreeBullet::checkCollision(BaseObject* object, float dt)
{
	return 0;
}
