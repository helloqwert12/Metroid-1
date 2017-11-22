#include "BombBall.h"

BombBall::BombBall(int x, int y) : BaseObject(BOMB_BALL)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::ITEM);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ITEM, "bomb_01"));
	_sprite->setPosition(x, y);

	_animation = new Animation(_sprite, 0.1f);
	_animation->addFrameRect(eID::ITEM, "bomb_01", "bomb_02", "bomb_03", "bomb_04", NULL);
}

void BombBall::init()
{
	auto collisionBody = new CollisionBody(this);	
	_componentList["CollisionBody"] = collisionBody;
}

void BombBall::update(float deltatime)
{
	_animation->update(deltatime);

	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		it->second->update(deltatime);
	}
}

void BombBall::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	_animation->draw(spriteHandle, viewport);
}

void BombBall::release()
{
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

float BombBall::checkCollision(BaseObject* object, float dt)
{
	return 0;
}
