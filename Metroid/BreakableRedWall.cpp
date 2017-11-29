#include "BreakableRedWall.h"

BreakableRedWall::BreakableRedWall(int x, int y) : BaseObject(BREAKABLE_RED_WALL)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::BREAKABLE_WALL);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BREAKABLE_WALL, "breakable_red_wall_01"));
	_sprite->setPosition(x, y);

	_animation = new Animation(_sprite, 1.0f);
	_animation->addFrameRect(eID::BREAKABLE_WALL, "breakable_red_wall_01", NULL);

	_effect = SpriteManager::getInstance()->getSprite(eID::BULLET_EFFECT);
	_effect->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BULLET_EFFECT, "explosion_01"));
	_effectAnimation = new Animation(_effect, 0.1);
	_effectAnimation->addFrameRect(BULLET_EFFECT, "explosion_01", "explosion_02", "explosion_03", NULL);

	_hitPoint = 1;
}

void BreakableRedWall::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;

	_effectStopWatch = new StopWatch();
}

void BreakableRedWall::update(float deltatime)
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

		if (_effectStopWatch->isStopWatch(200))
		{
			this->setStatus(DESTROY);
		}
	}
}

void BreakableRedWall::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	if (_hitPoint > 0)
		_animation->draw(spriteHandle, viewport);
	else
		_effectAnimation->draw(spriteHandle, viewport);
}

void BreakableRedWall::release()
{
	SAFE_DELETE(_animation);
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

void BreakableRedWall::wasHit(int hitPoint)
{
	_hitPoint -= hitPoint;
}

bool BreakableRedWall::isDead()
{
	return (_hitPoint <= 0);
}

float BreakableRedWall::checkCollision(BaseObject* object, float dt)
{
	return 0;
}
