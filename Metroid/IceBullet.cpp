#include "IceBullet.h"

IceBullet::IceBullet(int x, int y, bool direct) : Weapon(ICE_BULLET)
{
	_sprite = SpriteManager::getInstance()->getSprite(BULLET_EFFECT);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BULLET_EFFECT, "i_bullet_01"));
	_sprite->setPosition(x, y);

	auto movement = new Movement(GVector2(0, 0), GVector2(0, 0), _sprite);
	_componentList["Movement"] = movement;

	if (direct)
	{
		movement->setVelocity(GVector2(ICE_BULLET_SPEED, 0));
	}
	else
	{
		_sprite->setScaleX(-1);
		movement->setVelocity(GVector2(-ICE_BULLET_SPEED, 0));
	}
}

void IceBullet::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;
}

void IceBullet::update(float deltatime)
{
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		it->second->update(deltatime);
	}
}

void IceBullet::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	_sprite->render(spriteHandle, viewport);
}

void IceBullet::release()
{
}
