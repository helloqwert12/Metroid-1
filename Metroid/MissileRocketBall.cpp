#include "MissileRocketBall.h"

MissileRocketBall::MissileRocketBall(int x, int y) : BaseObject(MISSILE_ROCKET_BALL)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::ITEM);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ITEM, "missile_rocket_01"));
	_sprite->setPosition(x, y);

	_animation = new Animation(_sprite, 0.1f);
	_animation->addFrameRect(eID::ITEM, "missile_rocket_01", "missile_rocket_02", "missile_rocket_03", "missile_rocket_04", NULL);
}

void MissileRocketBall::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;
}

void MissileRocketBall::update(float deltatime)
{
	_animation->update(deltatime);

	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		it->second->update(deltatime);
	}
}

void MissileRocketBall::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	_animation->draw(spriteHandle, viewport);
}

void MissileRocketBall::release()
{
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

float MissileRocketBall::checkCollision(BaseObject* object, float dt)
{
	return 0;
}
