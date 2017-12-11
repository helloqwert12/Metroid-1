#include "Zeebetite.h"

Zeebetite::Zeebetite(int x, int y) : BaseObject(ZEEBETITE)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::BOSS_STAGE);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BOSS_STAGE, "zeebetite_01"));
	_sprite->setPosition(x, y);

	_effect = SpriteManager::getInstance()->getSprite(eID::BULLET_EFFECT);
	_effect->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BULLET_EFFECT, "explosion_01"));
	_effectAnimation = new Animation(_effect, 0.1f, false);
	_effectAnimation->addFrameRect(BULLET_EFFECT, "explosion_01", "explosion_02", "explosion_03", NULL);

	_hitPoint = 40;
}

void Zeebetite::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;

	_effectStopWatch = new StopWatch();
}

void Zeebetite::update(float deltatime)
{
	if (_hitPoint > 0)
	{
		if (_hitPoint > 30)
			_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BOSS_STAGE, "zeebetite_01"));
		else if (_hitPoint > 20 && _hitPoint <= 30)
			_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BOSS_STAGE, "zeebetite_02"));
		else if (_hitPoint > 10 && _hitPoint <= 20)
			_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BOSS_STAGE, "zeebetite_03"));
		else
			_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BOSS_STAGE, "zeebetite_04"));

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

void Zeebetite::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	if (_hitPoint > 0)
		_sprite->render(spriteHandle, viewport);
	else
		_effectAnimation->draw(spriteHandle, viewport);
}

void Zeebetite::release()
{
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

void Zeebetite::wasHit(int hitPoint)
{
	_hitPoint -= hitPoint;
}

bool Zeebetite::isDead()
{
	return (_hitPoint <= 0);
}

float Zeebetite::checkCollision(BaseObject* object, float dt)
{
	return 0;
}
