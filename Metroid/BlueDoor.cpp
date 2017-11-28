#include "BlueDoor.h"

BlueDoor::BlueDoor(int x, int y) : BaseObject(BLUE_DOOR)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::DOOR);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::DOOR, "blue_door_01"));
	_sprite->setPosition(x, y);

	_animation = new Animation(_sprite, 1.0f);
	_animation->addFrameRect(eID::DOOR, "blue_door_01", NULL);

	_effect = SpriteManager::getInstance()->getSprite(eID::DOOR);
	_effect->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::DOOR, "blue_door_01"));
	_effectAnimation = new Animation(_effect, 0.15f, false);
	_effectAnimation->addFrameRect(DOOR, "blue_door_01", "blue_door_02", "blue_door_03", "blue_door_04", "blue_door_05", NULL);

	_hitPoint = 1;
	_isClose = true;
}

void BlueDoor::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;
}

void BlueDoor::update(float deltatime)
{
	if (_hitPoint > 0)
	{
		_animation->update(deltatime);

		for (auto it = _componentList.begin(); it != _componentList.end(); it++)
		{
			it->second->update(deltatime);
		}
	}
	else
	{
		_effect->setPosition(this->getPosition());
		_effectAnimation->update(deltatime);

		if (!_effectAnimation->isAnimate())
		{
			_isClose = false;
		}
	}
}

void BlueDoor::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	if (_hitPoint > 0)
		_animation->draw(spriteHandle, viewport);
	else
		_effectAnimation->draw(spriteHandle, viewport);
}

void BlueDoor::release()
{
	SAFE_DELETE(_animation);
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

void BlueDoor::wasHit(int hitPoint)
{
	_hitPoint -= hitPoint;
}

bool BlueDoor::isDead()
{
	return (_hitPoint <= 0);
}

void BlueDoor::close()
{
	_isClose = true;
	_hitPoint = 1;

	// Restart lại animation do không lặp
	_effectAnimation->restart();
}

void BlueDoor::open()
{
	_isClose = false;
}

bool BlueDoor::isClose()
{
	return _isClose;
}

float BlueDoor::checkCollision(BaseObject* object, float dt)
{
	return 0;
}
