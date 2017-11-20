#include "NormalBullet.h"

NormalBullet::NormalBullet(int x, int y, eDirection direction) : Weapon(NORMAL_BULLET)
{
	_sprite = SpriteManager::getInstance()->getSprite(BULLET_EFFECT);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BULLET_EFFECT, "n_bullet_01"));
	_sprite->setPosition(x, y);

	auto movement = new Movement(GVector2(0, 0), GVector2(0, 0), _sprite);
	_componentList["Movement"] = movement;

	switch (direction)
	{
	case RIGHT:
		movement->setVelocity(GVector2(NORMAL_BULLET_SPEED, 0));
		break;
	case LEFT:
		_sprite->setScaleX(_sprite->getScale().x * (-1));
		movement->setVelocity(GVector2(-NORMAL_BULLET_SPEED, 0));
		break;
	default:
		break;
	}
}

void NormalBullet::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;
}

void NormalBullet::update(float deltatime)
{
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		it->second->update(deltatime);
	}
}

void NormalBullet::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	_sprite->render(spriteHandle, viewport);
}

void NormalBullet::release()
{
}
