#include "LongBeam.h"

LongBeam::LongBeam(int x, int y) : BaseObject(LONG_BEAM)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::ITEM);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ITEM, "long_beam_01"));
	_sprite->setPosition(x, y);

	_animation = new Animation(_sprite, 0.05f);
	_animation->addFrameRect(eID::ITEM, "long_beam_01", "long_beam_02", "long_beam_03", "long_beam_04", NULL);
}

void LongBeam::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;
}

void LongBeam::update(float deltatime)
{
	_animation->update(deltatime);

	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		it->second->update(deltatime);
	}
}

void LongBeam::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	_animation->draw(spriteHandle, viewport);
}

void LongBeam::release()
{
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

float LongBeam::checkCollision(BaseObject* object, float dt)
{
	return 0;
}
