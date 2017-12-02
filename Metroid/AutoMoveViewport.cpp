#include "AutoMoveViewport.h"

AutoMoveViewport::AutoMoveViewport(int x, int y, int width, int height) : BaseObject(eID::AUTO_MOVE_VIEWPORT)
{
	this->_bound.left = x;
	this->_bound.bottom = y;
	this->_bound.top = y + height;
	this->_bound.right = x + width;
	this->setPhysicsBodySide(eDirection::ALL);
}

void AutoMoveViewport::init()
{
	this->_sprite = nullptr;
	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;
}

void AutoMoveViewport::update(float deltatime)
{
	for (auto it : _listComponent)
	{
		it.second->update(deltatime);
	}
}

void AutoMoveViewport::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
}

void AutoMoveViewport::release()
{
	for (auto it : _listComponent)
	{
		SAFE_DELETE(it.second);
	}
	_listComponent.clear();
}

GVector2 AutoMoveViewport::getPosition()
{
	return GVector2(_bound.left, _bound.top);
}

void AutoMoveViewport::setPosition(GVector2 position)
{
	_bound.left = position.x;
	_bound.top = position.y;
}

RECT AutoMoveViewport::getBounding()
{
	return _bound;
}
