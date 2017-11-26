#include "Viewport.h"

Viewport::Viewport(float x, float y, float width, float height)
{
	_positionWorld.x = x;
	_positionWorld.y = y;
	_width = width;
	_height = height;
}

Viewport::~Viewport()
{
}

void Viewport::setPositionWorld(GVector2 position)
{
	if (_positionWorld != position)
		_positionWorld = position;
}

GVector2 Viewport::getPositionWorld()
{
	return _positionWorld;
}

float Viewport::getWidth()
{
	return _width;
}

float Viewport::getHeight()
{
	return _height;
}

GVector3 Viewport::getPositionInViewport(GVector3* position)
{
	D3DXMATRIX matrix;
	D3DXVECTOR4 positionInViewport;

	D3DXMatrixIdentity(&matrix);
	matrix._22 = -1.0f;
	matrix._41 = (-1) * _positionWorld.x;
	matrix._42 = _positionWorld.y;

	D3DXVec3Transform(&positionInViewport, position, &matrix);

	return GVector3(positionInViewport.x, positionInViewport.y, positionInViewport.z);
}

RECT Viewport::getBounding()
{
	RECT rect;
	rect.left = _positionWorld.x;
	rect.top = _positionWorld.y;
	rect.right = rect.left + _width;
	rect.bottom = rect.top - _height;

	return rect;
}
