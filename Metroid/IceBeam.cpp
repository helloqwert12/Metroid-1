#include "IceBeam.h"

IceBeam::IceBeam(int x, int y) : BaseObject(ICE_BEAM)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::ITEM);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ITEM, "ice_beam_01"));
	_sprite->setPosition(x, y);

	_animation = new Animation(_sprite, 0.1f);
	_animation->addFrameRect(eID::ITEM, "ice_beam_01", "ice_beam_02", "ice_beam_03", "ice_beam_04", NULL);
}

void IceBeam::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;
}

void IceBeam::update(float deltatime)
{
	_animation->update(deltatime);

	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		it->second->update(deltatime);
	}
}

void IceBeam::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	_animation->draw(spriteHandle, viewport);
}

void IceBeam::release()
{
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

float IceBeam::checkCollision(BaseObject* object, float dt)
{
	return 0;
}
