#include "ChangeMapDirection.h"

ChangeMapDirection::ChangeMapDirection(int x, int y, int width, int height, eMapDirection mapDirection) : BaseObject(eID::CHANGE_MAP_DIRECTION)
{
	this->_bound.left = x;
	this->_bound.bottom = y;
	this->_bound.top = y + height;
	this->_bound.right = x + width;
	this->setPhysicsBodySide(eDirection::ALL);

	this->_mapDirection = mapDirection;
}

void ChangeMapDirection::init()
{
	this->_sprite = nullptr;
	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;
}

void ChangeMapDirection::update(float deltatime)
{
	for (auto it : _listComponent)
	{
		it.second->update(deltatime);
	}
}

void ChangeMapDirection::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
}

void ChangeMapDirection::release()
{
	for (auto it : _listComponent)
	{
		SAFE_DELETE(it.second);
	}
	_listComponent.clear();
}

GVector2 ChangeMapDirection::getPosition()
{
	return GVector2(_bound.left, _bound.top);
}

void ChangeMapDirection::setPosition(GVector2 position)
{
	_bound.left = position.x;
	_bound.top = position.y;
}

RECT ChangeMapDirection::getBounding()
{
	return _bound;
}

eMapDirection ChangeMapDirection::getMapDirection()
{
	return _mapDirection;
}
