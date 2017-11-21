#include "NormalBullet.h"

NormalBullet::NormalBullet(int x, int y, eDirection direction, int bulletRange) : Weapon(NORMAL_BULLET)
{
	_sprite = SpriteManager::getInstance()->getSprite(BULLET_EFFECT);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BULLET_EFFECT, "normal_bullet_01"));
	_sprite->setPosition(x, y);

	_initPosition = GVector2(x, y);
	_bulletRange = bulletRange;

	auto movement = new Movement(GVector2(0, 0), GVector2(0, 0), _sprite);
	_componentList["Movement"] = movement;

	switch (direction)
	{
	case TOP:
		_sprite->setRotate(-90);
		movement->setVelocity(GVector2(0, NORMAL_BULLET_SPEED));
		break;
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
	if (getDistance(this->getPosition(), _initPosition) > _bulletRange)
	{
		this->setStatus(eStatus::DESTROY);
	}

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

CollisionBody* NormalBullet::getCollisionBody()
{
	return (CollisionBody*)_componentList["CollisionBody"];
}
