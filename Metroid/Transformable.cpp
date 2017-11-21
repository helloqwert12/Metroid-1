#include "Transformable.h"

Transformable::Transformable()
{
	_scale = GVector2(1.0f, 1.0f);
}

Transformable::~Transformable()
{
}

GVector2 Transformable::getPosition()
{
	return _position;
}

float Transformable::getPositionX()
{
	return _position.x;
}

float Transformable::getPositionY()
{
	return _position.y;
}

void Transformable::setPosition(GVector2 position)
{
	this->_position = GVector2(position.x, position.y);
}

void Transformable::setPosition(float x, float y)
{
	this->setPositionX(x);
	this->setPositionY(y);
}

void Transformable::setPositionX(float x)
{
	if (_position.x != x)
		_position.x = x;
}

void Transformable::setPositionY(float y)
{
	if (_position.y != y)
		_position.y = y;
}

GVector2 Transformable::getScale()
{
	return _scale;
}

void Transformable::setScale(GVector2 scale)
{
	if (_scale != scale)
		_scale = scale;
}

void Transformable::setScale(float scale)
{
	if (_scale.x != scale || _scale.y != scale)
	{
		_scale.x = scale;
		_scale.y = scale;
	}
}

void Transformable::setScaleX(float scaleX)
{
	if (_scale.x != scaleX)
		_scale.x = scaleX;
}

void Transformable::setScaleY(float scaleY)
{
	if (_scale.y != scaleY)
		_scale.y = scaleY;
}

float Transformable::getRotate()
{
	return _rotate;
}

void Transformable::setRotate(float degree)
{
	if (_rotate != degree)
		_rotate = degree;
}

GVector2 Transformable::getOrigin()
{
	return _origin;
}

void Transformable::setOrigin(GVector2 origin)
{
	if (_origin != origin)
		_origin = origin;
}

void Transformable::setZIndex(float zIndex)
{
	if (_zIndex != zIndex)
		_zIndex = zIndex;
}

float Transformable::getZIndex()
{
	return _zIndex;
}
