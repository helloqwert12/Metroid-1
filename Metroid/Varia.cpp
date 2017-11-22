#include "Varia.h"

Varia::Varia(int x, int y) : BaseObject(VARIA)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::ITEM);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ITEM, "varia_01"));
	_sprite->setPosition(x, y);

	_animation = new Animation(_sprite, 0.1f);
	_animation->addFrameRect(eID::ITEM, "varia_01", "varia_02", "varia_03", "varia_04", NULL);
}

void Varia::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;
}

void Varia::update(float deltatime)
{
	_animation->update(deltatime);

	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		it->second->update(deltatime);
	}
}

void Varia::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	_animation->draw(spriteHandle, viewport);
}

void Varia::release()
{
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

float Varia::checkCollision(BaseObject* object, float dt)
{
	return 0;
}
