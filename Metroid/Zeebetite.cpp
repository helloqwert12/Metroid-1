#include "Zeebetite.h"

Zeebetite::Zeebetite(int x, int y) : BaseObject(ZEEBETITE)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::BOSS_STAGE);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BOSS_STAGE, "zeebetite_01"));
	_sprite->setPosition(x, y);

	for (auto i = 0; i < 4; i++)
		_animation.push_back(new Animation(_sprite, 1.0f));

	_animation[0]->addFrameRect(eID::BOSS_STAGE, "zeebetite_01", NULL);
	_animation[1]->addFrameRect(eID::BOSS_STAGE, "zeebetite_02", NULL);
	_animation[2]->addFrameRect(eID::BOSS_STAGE, "zeebetite_03", NULL);
	_animation[3]->addFrameRect(eID::BOSS_STAGE, "zeebetite_04", NULL);

	_effect = SpriteManager::getInstance()->getSprite(eID::BULLET_EFFECT);
	_effect->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BULLET_EFFECT, "explosion_01"));
	_effectAnimation = new Animation(_effect, 0.1f, false);
	_effectAnimation->addFrameRect(BULLET_EFFECT, "explosion_01", "explosion_02", "explosion_03", NULL);

	_hitPoint = 100;
}

void Zeebetite::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;

	_animationIndex = 0;
	_effectStopWatch = new StopWatch();
}

void Zeebetite::update(float deltatime)
{
	if (_hitPoint > 0)
	{
		if (_hitPoint > 75)
			_animationIndex = 0;
		else if (_hitPoint > 50 && _hitPoint <= 75)
			_animationIndex = 1;
		else if (_hitPoint > 25 && _hitPoint <= 50)
			_animationIndex = 2;
		else
			_animationIndex = 3;

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
		_animation[_animationIndex]->draw(spriteHandle, viewport);
	else
		_effectAnimation->draw(spriteHandle, viewport);
}

void Zeebetite::release()
{
	for (auto it = _animation.begin(); it != _animation.end(); it++)
	{
		SAFE_DELETE(*it);
	}

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
