#include "RedItemBall.h"

RedItemBall::RedItemBall(int x, int y) : BaseObject(RED_ITEM_BALL)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::ITEM_BALL);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ITEM_BALL, "red_item_ball_01"));
	_sprite->setPosition(x, y);

	_animation = new Animation(_sprite, 1.0f);
	_animation->addFrameRect(eID::ITEM_BALL, "red_item_ball_01", NULL);

	_effect = SpriteManager::getInstance()->getSprite(eID::ITEM_BALL);
	_effect->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ITEM_BALL, "red_item_ball_01"));
	_effectAnimation = new Animation(_effect, 0.25f, false);
	_effectAnimation->addFrameRect(ITEM_BALL, "red_item_ball_01", "red_item_ball_02", "red_item_ball_03", NULL);

	_hitPoint = 2;
}

void RedItemBall::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;
}

void RedItemBall::update(float deltatime)
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
			this->setStatus(DESTROY);
		}
	}
}

void RedItemBall::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	if (_hitPoint > 0)
		_animation->draw(spriteHandle, viewport);
	else
		_effectAnimation->draw(spriteHandle, viewport);
}

void RedItemBall::release()
{
	SAFE_DELETE(_animation);
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

void RedItemBall::wasHit(int hitPoint)
{
	_hitPoint -= hitPoint;
}

bool RedItemBall::isDead()
{
	return (_hitPoint <= 0);
}

float RedItemBall::checkCollision(BaseObject* object, float dt)
{
	return 0;
}
