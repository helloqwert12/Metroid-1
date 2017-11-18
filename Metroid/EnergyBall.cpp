#include "EnergyBall.h"

EnergyBall::EnergyBall(int x, int y) : BaseObject(ENERGY_BALL)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::ITEM);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ITEM, "enegy_ball_01"));
	_sprite->setPosition(x, y);

	_animation = new Animation(_sprite, 0.07f);
	_animation->addFrameRect(eID::ITEM, "enegy_ball_01", "enegy_ball_02", NULL);
}

void EnergyBall::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;

	_destroyStopWatch = new StopWatch();
}

void EnergyBall::update(float deltatime)
{
	_animation->update(deltatime);

	// Sau một khoảng thời gian thì sẽ tự biến mất
	if (_destroyStopWatch->isStopWatch(ENERGY_BALL_DESTROY_TIME))
	{
		this->setStatus(DESTROY);
	}
	
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		it->second->update(deltatime);
	}
}

void EnergyBall::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	_animation->draw(spriteHandle, viewport);
}

void EnergyBall::release()
{
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

float EnergyBall::checkCollision(BaseObject* object, float dt)
{
	return 0;
}
