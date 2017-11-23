#include "BaseObject.h"

BaseObject::BaseObject(eID id)
{
	this->_id = id;
	this->_sprite = nullptr;
	this->setStatus(eStatus::NORMAL);
	this->setPhysicsBodySide(eDirection::ALL);
}

BaseObject::~BaseObject()
{
}

eID BaseObject::getId()
{
	return this->_id;
}

eStatus BaseObject::getStatus()
{
	return this->_status;
}

void BaseObject::setStatus(eStatus status)
{
	if (_status != status)
		_status = status;
}

void BaseObject::addStatus(eStatus status)
{
	this->setStatus(eStatus(this->getStatus() | status));
}

void BaseObject::removeStatus(eStatus status)
{
	this->setStatus(eStatus(this->getStatus() & ~status));
}

bool BaseObject::isInStatus(eStatus status)
{
	return (this->getStatus() & status) == status;
}

GVector2 BaseObject::getPosition()
{
	return _sprite->getPosition();
}

float BaseObject::getPositionX()
{
	return _sprite->getPositionX();
}

float BaseObject::getPositionY()
{
	return _sprite->getPositionY();
}

void BaseObject::setPosition(GVector2 position)
{
	_sprite->setPosition(position);
}

void BaseObject::setPosition(float x, float y)
{
	_sprite->setPosition(x, y);
}

void BaseObject::setPositionX(float x)
{
	_sprite->setPositionX(x);
}

void BaseObject::setPositionY(float y)
{
	_sprite->setPositionY(y);
}

GVector2 BaseObject::getScale()
{
	return _sprite->getScale();
}

void BaseObject::setScale(GVector2 scale)
{
	_sprite->setScale(scale);
}

void BaseObject::setScale(float scale)
{
	_sprite->setScale(scale);
}

void BaseObject::setScaleX(float scaleX)
{
	_sprite->setScaleX(scaleX);
}

void BaseObject::setScaleY(float scaleY)
{
	_sprite->setScaleY(scaleY);
}

GVector2 BaseObject::getOrigin()
{
	return _sprite->getOrigin();
}

void BaseObject::setOrigin(GVector2 origin)
{
	_sprite->setOrigin(origin);
}

float BaseObject::getRotate()
{
	return _sprite->getRotate();
}

void BaseObject::setRotate(float degree)
{
	_sprite->setRotate(degree);
}

void BaseObject::setZIndex(float z)
{
	_sprite->setZIndex(z);
}

float BaseObject::getZIndex()
{
	return _sprite->getZIndex();
}

void BaseObject::setOpacity(float opacity)
{
	_sprite->setOpacity(opacity);
}

float BaseObject::getOpacity()
{
	return _sprite->getOpacity();
}

void BaseObject::setColor(D3DXCOLOR color)
{
	if (_sprite != nullptr)
		_sprite->setColor(color);
}

D3DXCOLOR BaseObject::getColor()
{
	return _sprite->getColor();
}

RECT BaseObject::getBounding()
{
	return _sprite->getBounding();
}

float BaseObject::checkCollision(BaseObject* object, float dt)
{
	return 0.0f;
}

GVector2 BaseObject::getVelocity()
{
	return GVector2(0, 0);
}

void BaseObject::setPhysicsBodySide(eDirection side)
{
	if (_physicsSide != side)
		_physicsSide = side;
}

eDirection BaseObject::getPhysicsBodySide()
{
	return _physicsSide;
}

Controlable::Controlable()
{
	_input = InputController::getInstance();
}
