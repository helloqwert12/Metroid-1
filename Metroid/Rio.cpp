#include "Rio.h"
#include "SoundManager.h"

Rio::Rio(int x, int y, bool direction) : BaseObject(RIO)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::ENEMY);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ENEMY, "yellow_rio_01"));
	_sprite->setPosition(x, y);

	_animation = new Animation(_sprite, 0.2f);
	_animation->addFrameRect(eID::ENEMY, "yellow_rio_01", "yellow_rio_02", NULL);

	_effect = SpriteManager::getInstance()->getSprite(eID::BULLET_EFFECT);
	_effect->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BULLET_EFFECT, "explosion_01"));
	_effectAnimation = new Animation(_effect, 0.1);
	_effectAnimation->addFrameRect(BULLET_EFFECT, "explosion_01", "explosion_02", "explosion_03", NULL);

	_hitPoint = 5;
	_isActive = false;

	auto movement = new Movement(GVector2(0, 0), GVector2(0, 0), _sprite);
	_componentList["Movement"] = movement;

	if (!direction)
	{
		_sprite->setScaleX(_sprite->getScale().x * (-1));
	}
}

void Rio::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;

	_effectStopWatch = new StopWatch();
	_hitStopWatch = new StopWatch();
	_startHitStopWatch = false;
}

void Rio::update(float deltatime)
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
			SoundManager::getInstance()->play(eSoundID::EXPLOSION_SOUND);

			this->setStatus(DESTROY);

			srand(time(0));
			auto random = rand() % 10;
			BaseObject* item = nullptr;
			if (random < 5)
				item = new EnergyBall(this->getPositionX(), this->getPositionY());
			if (item != nullptr)
			{
				item->init();
				QuadTreeNode::getInstance()->insert(item);
			}
		}
	}
}

void Rio::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	if (_hitPoint > 0)
		_animation->draw(spriteHandle, viewport);
	else
		_effectAnimation->draw(spriteHandle, viewport);
}

void Rio::release()
{
	SAFE_DELETE(_animation);
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

void Rio::wasHit(int hitPoint)
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

bool Rio::isDead()
{
	return (_hitPoint <= 0);
}

void Rio::active(bool direction)
{
	_isActive = true;

	auto sinMovement = new SinMovement(GVector2(0, 200), 0.5, _sprite);
	this->_componentList["SinMovement"] = sinMovement;

	auto movement = (Movement*)this->_componentList["Movement"];
	if (direction)
	{
		movement->setVelocity(GVector2(RIO_MOVE_SPEED, 0));
	}
	else
	{
		_sprite->setScaleX(_sprite->getScale().x * -1);
		movement->setVelocity(GVector2(-RIO_MOVE_SPEED, 0));
	}
}

void Rio::deactive()
{
	_isActive = false;

	auto movement = (Movement*)this->_componentList["Movement"];
	movement->setVelocity(GVector2(0, 0));

	auto sinMovement = (Movement*)this->_componentList["SinMovement"];
	_componentList.erase("SinMovement");
	delete sinMovement;
}

bool Rio::isActive()
{
	return _isActive;
}

float Rio::checkCollision(BaseObject* object, float dt)
{
	auto objectId = object->getId();
	if (objectId == WALL || objectId == BREAKABLE_BLUE_WALL || objectId == BREAKABLE_RED_WALL || objectId == BLUE_DOOR || objectId == RED_DOOR)
	{
		auto collisionBody = (CollisionBody*)_componentList["CollisionBody"];
		eDirection direction;
		if (collisionBody->checkCollision(object, direction, dt, true))
		{
			// Va chạm Wall LEFT hoặc RIGHT thì đi ngược lại
			if (direction == LEFT || direction == RIGHT)
			{
				auto movement = (Movement*)this->_componentList["Movement"];
				movement->setVelocity(GVector2(-movement->getVelocity().x, 0));
				this->setScaleX(this->getScale().x * -1);
			}
			return 1.0f;
		}
	}
	return 0;
}
