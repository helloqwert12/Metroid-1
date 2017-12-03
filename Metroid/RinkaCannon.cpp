#include "RinkaCannon.h"

RinkaCannon::RinkaCannon(int x, int y, int width, int height) : BaseObject(RINKA_CANNON)
{
	this->_bound.left = x;
	this->_bound.bottom = y;
	this->_bound.top = y + height;
	this->_bound.right = x + width;
	this->setPhysicsBodySide(eDirection::ALL);

	_isActive = false;
}

void RinkaCannon::init()
{
	this->_sprite = nullptr;
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;

	_rinkaAppearStopWatch = new StopWatch();
}

void RinkaCannon::update(float deltatime)
{
	if (_isActive)
	{
		if (_rinkaAppearStopWatch->isStopWatch(RINKA_APPEAR_TIME))
		{
			Rinka* rinka = new Rinka((_bound.left + _bound.right) / 2, (_bound.top + _bound.bottom) / 2, GVector2(20, 0));
			rinka->init();
			QuadTreeNode::getInstance()->insert(rinka);

			_rinkaAppearStopWatch->restart();
		}
	}
}

void RinkaCannon::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
}

void RinkaCannon::release()
{
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

GVector2 RinkaCannon::getPosition()
{
	return GVector2(_bound.left, _bound.top);
}

void RinkaCannon::setPosition(GVector2 position)
{
	_bound.left = position.x;
	_bound.top = position.y;
}

RECT RinkaCannon::getBounding()
{
	return _bound;
}

void RinkaCannon::active()
{
	_isActive = true;
}

void RinkaCannon::deactive()
{
	_isActive = false;
}

bool RinkaCannon::isActive()
{
	return _isActive;
}

float RinkaCannon::checkCollision(BaseObject* object, float dt)
{
	return 0;
}
