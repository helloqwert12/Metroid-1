#include "Sprite.h"

Sprite::Sprite(LPD3DXSPRITE spriteHandle, LPWSTR filePath, int totalFrames, int cols)
{
	_origin = GVector2(0.5f, 0.5f);
	_scale = GVector2(1.0f, 1.0f);
	_zIndex = 1;
	_rotate = 0.0f;

	auto rs = _texture.loadFromFile(spriteHandle, filePath);
	if (rs != D3D_OK)
		throw;

	_totalFrames = totalFrames;
	_columns = cols;
	_textureWidth = _texture.getWidth();
	_textureHeight = _texture.getHeight();
	_frameWidth = _textureWidth / cols;
	_frameHeight = _textureHeight * cols / totalFrames;
	_index = 0;
	_currentFrame = GVector2(0, 0);

	this->setIndex(0);
	this->updateBounding();
}

Sprite::~Sprite()
{
}

void Sprite::release()
{
	this->_texture.release();
}

void Sprite::render(LPD3DXSPRITE spriteHandle)
{
	_texture.render(
		spriteHandle,
		&_frameRect,
		GVector2((int)_position.x, (int)_position.y),
		_scale,
		_rotate,
		_origin,
		_zIndex
	);
}

void Sprite::render(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	_texture.render(
		spriteHandle,
		&_frameRect,
		*viewport,
		_position,
		_scale,
		_rotate,
		_origin,
		_zIndex
	);
}

void Sprite::setPosition(float x, float y, float z)
{
	GVector3 v(x, y, z);
	this->setPosition(v);
}

void Sprite::setPosition(GVector3 vector)
{
	this->_position = GVector2(vector.x, vector.y);
	this->updateBounding();
}

void Sprite::setPosition(GVector2 position)
{
	this->_position = GVector2(position.x, position.y);
	this->updateBounding();
}

void Sprite::setPositionX(float x)
{
	if (x == _position.x)
		return;

	_position.x = x;
	this->updateBounding();
}

void Sprite::setPositionY(float y)
{
	if (y == _position.y)
		return;

	_position.y = y;
	this->updateBounding();
}

void Sprite::setScale(GVector2 scale)
{
	if (scale == _scale)
		return;

	_scale = scale;
	this->updateBounding();
}

void Sprite::setScale(float scale)
{
	if (scale != _scale.x || scale != _scale.y)
	{
		_scale.x = scale;
		_scale.y = scale;
		this->updateBounding();
	}
}

void Sprite::setScaleX(float sx)
{
	if (sx == _scale.x)
		return;

	_scale.x = sx;
	this->updateBounding();
}

void Sprite::setScaleY(float sy)
{
	if (sy == _scale.y)
		return;

	_scale.y = sy;
	this->updateBounding();
}

void Sprite::setRotate(float degree)
{
	if (degree == _rotate)
		return;

	_rotate = degree;
	this->updateBounding();
}

void Sprite::setOrigin(GVector2 origin)
{
	if (origin == _origin)
		return;

	_origin = origin;
	this->updateBounding();
}

void Sprite::setZIndex(float z)
{
	if (z != _zIndex)
		_zIndex = z;
}

RECT Sprite::getBounding()
{
	return _bound;
}

void Sprite::setFrameRect(RECT rect)
{
	_frameRect = rect;

	_frameWidth = abs(_frameRect.left - _frameRect.right);
	_frameHeight = abs(_frameRect.top - _frameRect.bottom);

	this->updateBounding();
}

void Sprite::setFrameRect(float top, float right, float bottom, float left)
{
	_frameRect.top = top;
	_frameRect.right = right;
	_frameRect.left = left;
	_frameRect.bottom = bottom;

	_frameWidth = abs(_frameRect.left - _frameRect.right);
	_frameHeight = abs(_frameRect.top - _frameRect.bottom);

	this->updateBounding();
}

void Sprite::setFrameRect(float x, float y, int width, int height)
{
	_frameRect.top = y;
	_frameRect.right = x + width;
	_frameRect.left = x;
	_frameRect.bottom = y + height;

	_frameWidth = width;
	_frameHeight = height;

	this->updateBounding();
}

RECT Sprite::getFrameRect()
{
	return _frameRect;
}

RECT Sprite::getFrameRectByIndex(int index)
{
	index = index % _totalFrames;

	this->setIndex(index);

	RECT rect;
	rect.left = (long)_currentFrame.x * _frameWidth;
	rect.right = _frameRect.left + _frameWidth;
	rect.top = (long)_currentFrame.y * _frameHeight;
	rect.bottom = _frameRect.top + _frameHeight;

	return rect;
}

int Sprite::getFrameWidth()
{
	return _frameWidth * abs(_scale.x);
}

int Sprite::getFrameHeight()
{
	return _frameHeight * abs(_scale.y);
}

int Sprite::getTextureWidth()
{
	return _textureWidth * abs(_scale.x);
}

int Sprite::getTextureHeight()
{
	return _textureHeight * abs(_scale.y);
}

void Sprite::setOpacity(float opacity)
{
	if (_opacity == opacity)
		return;

	_opacity = opacity;
	_texture.setColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, _opacity));
}

float Sprite::getOpacity()
{
	return _opacity;
}

void Sprite::setColor(D3DXCOLOR color)
{
	_color = color;
	_texture.setColor(_color);
}

D3DXCOLOR Sprite::getColor()
{
	return _color;
}

void Sprite::nextFrame()
{
	if (_totalFrames <= 1)
		return;

	this->setIndex(_index + 1);
}

void Sprite::setIndex(int index)
{
	if (_index != index)
		_index = index;

	this->setCurrentFrame();
}

void Sprite::setCurrentFrame()
{
	if (_index >= _totalFrames)
		_index = _index % _totalFrames;

	this->_currentFrame.x = _index % _columns;
	this->_currentFrame.y = _index / _columns;

	this->setFrameRect();
}

void Sprite::setFrameRect()
{
	this->_frameRect.left = (long)_currentFrame.x * _frameWidth;
	this->_frameRect.right = _frameRect.left + _frameWidth;
	this->_frameRect.top = (long)_currentFrame.y * _frameHeight;
	this->_frameRect.bottom = _frameRect.top + _frameHeight;
}

void Sprite::updateBounding()
{
	float scaledWidth = _frameWidth * abs(_scale.x);
	float scaledHeight = _frameHeight * abs(_scale.y);

	// position là vị trí chính giữa lúc vẽ
	this->_bound.left = _position.x - scaledWidth * _origin.x;
	this->_bound.bottom = _position.y - scaledHeight * _origin.y;
	this->_bound.right = _bound.left + scaledWidth;
	this->_bound.top = _bound.bottom + scaledHeight;
}
