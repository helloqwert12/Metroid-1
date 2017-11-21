#include "Bomb.h"

Bomb::Bomb(int x, int y) : Weapon(BOMB)
{
	_sprite = SpriteManager::getInstance()->getSprite(BULLET_EFFECT);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BULLET_EFFECT, "bomb_01"));
	_sprite->setPosition(x, y);

	_animation = new Animation(_sprite, 0.07f);
	_animation->addFrameRect(eID::BULLET_EFFECT, "bomb_01", "bomb_02", NULL);

	_effect = SpriteManager::getInstance()->getSprite(eID::BULLET_EFFECT);
	_effect->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BULLET_EFFECT, "explosion_01"));
	_effectAnimation = new Animation(_effect, 0.1);
	_effectAnimation->addFrameRect(BULLET_EFFECT, "explosion_01", "explosion_02", "explosion_03", NULL);

	auto movement = new Movement(GVector2(0, 0), GVector2(0, 0), _sprite);
	_componentList["Movement"] = movement;
}

void Bomb::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;

	_effectStopWatch = new StopWatch();

	_isExploded = false;
	_explodeStopWatch = new StopWatch();
}

void Bomb::update(float deltatime)
{
	if (!_isExploded)
	{
		_animation->update(deltatime);

		// Sau một khoảng thời gian thì bomb nổ
		if (_explodeStopWatch->isStopWatch(BOMB_EXPLODE_TIME))
		{
			this->explode();
		}
	}
	else
	{
		_effect->setPosition(this->getPosition());
		_effectAnimation->update(deltatime);

		if (_effectStopWatch->isStopWatch(200))
		{
			this->setStatus(eStatus::DESTROY);
		}
	}

	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		it->second->update(deltatime);
	}
}

void Bomb::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	if (!_isExploded)
		_animation->draw(spriteHandle, viewport);
	else
		_effectAnimation->draw(spriteHandle, viewport);
}

void Bomb::release()
{
}

void Bomb::explode()
{
	_isExploded = true;
}
