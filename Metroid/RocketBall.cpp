#include "RocketBall.h"

RocketBall::RocketBall(int x, int y) : BaseObject(ROCKET_BALL)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::ITEM);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ITEM, "rocket_ball_01"));
	_sprite->setPosition(x, y);

	_animation = new Animation(_sprite, 0.05f);
	_animation->addFrameRect(eID::ITEM, "rocket_ball_01", "rocket_ball_02", NULL);
}

void RocketBall::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;

	_destroyStopWatch = new StopWatch();
}

void RocketBall::update(float deltatime)
{
	_animation->update(deltatime);

	// Sau một khoảng thời gian thì sẽ tự biến mất
	if (_destroyStopWatch->isStopWatch(ROCKET_BALL_DESTROY_TIME))
	{
		this->setStatus(DESTROY);
	}

	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		it->second->update(deltatime);
	}
}

void RocketBall::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	_animation->draw(spriteHandle, viewport);
}

void RocketBall::release()
{
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

float RocketBall::checkCollision(BaseObject* object, float dt)
{
	return 0;
}
