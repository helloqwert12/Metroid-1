#include "Fire.h"

Fire::Fire(int x, int y, int width, int height) : BaseObject(eID::FIRE)
{
	this->_bound.left = x;
	this->_bound.bottom = y;
	this->_bound.top = y + height;
	this->_bound.right = x + width;
}

void Fire::init()
{
	this->_sprite = nullptr;
	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;
}

void Fire::update(float deltatime)
{
	for (auto it : _listComponent)
	{
		it.second->update(deltatime);
	}
}

void Fire::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
}

void Fire::release()
{
	for (auto it : _listComponent)
	{
		SAFE_DELETE(it.second);
	}
	_listComponent.clear();
}

GVector2 Fire::getPosition()
{
	return GVector2(_bound.left, _bound.top);
}

void Fire::setPosition(GVector2 position)
{
	_bound.left = position.x;
	_bound.top = position.y;
}

RECT Fire::getBounding()
{
	return _bound;
}
