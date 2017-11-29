#include "RedDoor.h"

RedDoor::RedDoor(int x, int y) : BaseObject(RED_DOOR)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::DOOR);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::DOOR, "red_door_01"));
	_sprite->setPosition(x, y);

	_animation = new Animation(_sprite, 1.0f);
	_animation->addFrameRect(eID::DOOR, "red_door_01", NULL);

	_effect = SpriteManager::getInstance()->getSprite(eID::DOOR);
	_effect->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::DOOR, "red_door_01"));
	_effectAnimation = new Animation(_effect, 0.1f, false);
	_effectAnimation->addFrameRect(DOOR, "red_door_01", "red_door_02", "red_door_03", "red_door_04", "red_door_05", NULL);

	_hitPoint = 25;
	_isClose = true;
}

void RedDoor::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;
}

void RedDoor::update(float deltatime)
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

void RedDoor::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	if (_hitPoint > 0)
		_animation->draw(spriteHandle, viewport);
	else
		_effectAnimation->draw(spriteHandle, viewport);
}

void RedDoor::release()
{
	SAFE_DELETE(_animation);
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

void RedDoor::wasHit(int hitPoint)
{
	_hitPoint -= hitPoint;
}

bool RedDoor::isDead()
{
	return (_hitPoint <= 0);
}

void RedDoor::close()
{
	_isClose = true;
	_hitPoint = 25;

	// Restart lại animation do không lặp
	_effectAnimation->restart();
}

void RedDoor::open()
{
	_isClose = false;
}

bool RedDoor::isClose()
{
	return _isClose;
}

float RedDoor::checkCollision(BaseObject* object, float dt)
{
	return 0;
}
