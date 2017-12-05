#include "CannonBullet.h"

CannonBullet::CannonBullet(int x, int y, eID cannonId) : BaseObject(CANNON_BULLET)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::BOSS_STAGE);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BOSS_STAGE, "cannon_bullet_01"));
	_sprite->setPosition(x, y);

	_initPosition = GVector2(x, y);

	_effect = SpriteManager::getInstance()->getSprite(eID::BULLET_EFFECT);
	_effect->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BULLET_EFFECT, "explosion_01"));
	_effectAnimation = new Animation(_effect, 0.1);
	_effectAnimation->addFrameRect(BULLET_EFFECT, "explosion_01", "explosion_02", "explosion_03", NULL);

	_hitPoint = 1;
	_isActive = true;
	
	switch (cannonId)
	{
	case LEFT_CANNON:
	{
		_velocity = GVector2(CANNON_BULLET_MOVE_SPEED, -CANNON_BULLET_MOVE_SPEED);
		_sprite->setRotate(135);
		break;
	}
	case MIDDLE_CANNON:
	{
		_velocity = GVector2(0, -CANNON_BULLET_MOVE_SPEED);
		_sprite->setRotate(180);
		break;
	}
	case RIGHT_CANNON:
	{
		_velocity = GVector2(-CANNON_BULLET_MOVE_SPEED, -CANNON_BULLET_MOVE_SPEED);
		_sprite->setRotate(235);
		break;
	}
	default:
		break;
	}

	Movement* movement = new Movement(GVector2(0, 0), _velocity, _sprite);
	_componentList["Movement"] = movement;
}

void CannonBullet::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;

	_effectStopWatch = new StopWatch();
	_hitStopWatch = new StopWatch();
	_startHitStopWatch = false;
}

void CannonBullet::update(float deltatime)
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

		// Nếu CannonBullet ra khỏi khoảng di chuyển thì DESTROY
		if (getDistance(this->getPosition(), _initPosition) > CANNON_BULLET_RANGE)
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

void CannonBullet::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	if (_hitPoint > 0)
		_sprite->render(spriteHandle, viewport);
	else
		_effectAnimation->draw(spriteHandle, viewport);
}

void CannonBullet::release()
{
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

void CannonBullet::wasHit(int hitPoint)
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

bool CannonBullet::isDead()
{
	return (_hitPoint <= 0);
}

void CannonBullet::active()
{
	_isActive = true;

	auto movement = (Movement*)this->_componentList["Movement"];
	movement->setVelocity(_velocity);
}

void CannonBullet::deactive()
{
	_isActive = false;

	auto movement = (Movement*)this->_componentList["Movement"];
	movement->setVelocity(GVector2(0, 0));
}

bool CannonBullet::isActive()
{
	return _isActive;
}

float CannonBullet::checkCollision(BaseObject* object, float dt)
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

				// Va chạm Wall thì DESTROY
				this->setStatus(DESTROY);
			}
			return 1.0f;
		}
	}
	return 0;
}
