#include "MotherBrain.h"

MotherBrain::MotherBrain(int x, int y) : BaseObject(MOTHER_BRAIN)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::BOSS_STAGE);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BOSS_STAGE, "mother_brain_normal_01"));
	_sprite->setPosition(x, y);

	for (auto i = 0; i < 2; i++)
		_animations.push_back(new Animation(_sprite, 0.1f));

	_animations[0]->addFrameRect(eID::BOSS_STAGE, "mother_brain_normal_01", "mother_brain_normal_02", "mother_brain_normal_03",
								"mother_brain_normal_04", "mother_brain_normal_05", "mother_brain_normal_06", 
								"mother_brain_normal_07", "mother_brain_normal_08" ,NULL);

	_animations[1]->addFrameRect(eID::BOSS_STAGE, "mother_brain_shield_break_01", "mother_brain_shield_break_02", "mother_brain_shield_break_03",
								"mother_brain_shield_break_04", "mother_brain_shield_break_05", "mother_brain_shield_break_06", 
								"mother_brain_shield_break_07", "mother_brain_shield_break_08", NULL);

	_effect = SpriteManager::getInstance()->getSprite(eID::BOSS_STAGE);
	_effect->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BOSS_STAGE, "mother_brain_explode_01"));
	_effectAnimation = new Animation(_effect, 0.1f);
	_effectAnimation->addFrameRect(BOSS_STAGE, "mother_brain_explode_01", "mother_brain_explode_02", NULL);

	_hitPoint = 200;
}

void MotherBrain::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;

	_animationIndex = 0;
	_effectStopWatch = new StopWatch();
	_hitStopWatch = new StopWatch();
	_startHitStopWatch = false;
}

void MotherBrain::update(float deltatime)
{
	if (_hitPoint > 0)
	{
		if (_hitPoint > 100)
			_animationIndex = 0;
		else
			_animationIndex = 1;

		_animations[_animationIndex]->update(deltatime);

		if (_startHitStopWatch)
		{
			// Check để sau khi hết khoảng thời gian protect thì tắt hitStopWatch
			if (_hitStopWatch->isStopWatch(200))
			{
				_startHitStopWatch = false;
				_hitStopWatch->restart();
				_animations[_animationIndex]->enableFlashes(false);
			}
		}

		for (auto it = _componentList.begin(); it != _componentList.end(); it++)
		{
			it->second->update(deltatime);
		}
	}
	else
	{
		_effect->setPosition(this->getPosition());
		_effectAnimation->update(deltatime);

		if (_effectStopWatch->isStopWatch(5000))
		{
			this->setStatus(DESTROY);
		}
	}
}

void MotherBrain::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	if (_hitPoint > 0)
		_animations[_animationIndex]->draw(spriteHandle, viewport);
	else
		_effectAnimation->draw(spriteHandle, viewport);
}

void MotherBrain::release()
{
	for (auto it = _animations.begin(); it != _animations.end(); it++)
	{
		SAFE_DELETE(*it);
	}

	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

void MotherBrain::wasHit(int hitPoint)
{
	if (!_startHitStopWatch)
	{
		_hitPoint -= hitPoint;
		_hitStopWatch->restart();
		_startHitStopWatch = true;
		_animations[_animationIndex]->enableFlashes(true);
	}
}

bool MotherBrain::isDead()
{
	return (_hitPoint <= 0);
}

float MotherBrain::checkCollision(BaseObject* object, float dt)
{
	return 0;
}
