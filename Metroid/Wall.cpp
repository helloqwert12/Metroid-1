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
	return;
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

float Wall::getPositionX()
{
	return _bound.left;
}

float Wall::getPositionY()
{
	return _bound.top;
}

void Wall::setPosition(GVector3 vector)
{
	_bound.left = vector.x;
	_bound.top = vector.y;
}

void Wall::setPosition(float x, float y, float z)
{
	_bound.left = x;
	_bound.top = y;
}

void Wall::setPosition(GVector2 position)
{
	_bound.left = position.x;
	_bound.top = position.y;
}

void Wall::setPosition(float x, float y)
{
	_bound.left = x;
	_bound.top = y;
}

void Wall::setPositionX(float x)
{
	_bound.left = x;
}

void Wall::setPositionY(float y)
{
	_bound.top = y;
}

float Wall::getRotate()
{
	return 0.0f;
}

float Wall::getZIndex()
{
	return 1; // hard code
}

RECT Wall::getBounding()
{
	return _bound;
}
