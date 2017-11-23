#include "Wall.h"

Wall::Wall(int x, int y, int width, int height) : BaseObject(eID::WALL)
{
	this->_bound.left = x;
	this->_bound.bottom = y;
	this->_bound.top = y + height;
	this->_bound.right = x + width;
	this->setPhysicsBodySide(eDirection::ALL);
}

Wall::~Wall()
{
}

void Wall::init()
{
	this->_sprite = nullptr;
	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;
}

void Wall::update(float deltatime)
{
	for (auto it : _listComponent)
	{
		it.second->update(deltatime);
	}
}

void Wall::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
}

void Wall::release()
{
	for (auto it : _listComponent)
	{
		SAFE_DELETE(it.second);
	}
	_listComponent.clear();
}

GVector2 Wall::getPosition()
{
	return GVector2(_bound.left, _bound.top);
}

void Wall::setPosition(GVector2 position)
{
	_bound.left = position.x;
	_bound.top = position.y;
}

RECT Wall::getBounding()
{
	return _bound;
}
