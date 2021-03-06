﻿#ifndef __TRANSFORMABLE_H__
#define __TRANSFORMABLE_H__

#include "define.h"

class Transformable
{
public:
	Transformable();
	~Transformable();

	virtual GVector2 getPosition();
	virtual float getPositionX();
	virtual float getPositionY();

	virtual void setPosition(GVector2 position);
	virtual void setPosition(float x, float y);
	virtual void setPositionX(float x);
	virtual void setPositionY(float y);

	virtual GVector2 getScale();
	virtual void setScale(GVector2 scale);
	virtual void setScale(float scale);
	virtual void setScaleX(float scaleX);
	virtual void setScaleY(float scaleY);

	virtual float getRotate();
	virtual void setRotate(float degree);

	virtual GVector2 getOrigin();
	virtual void setOrigin(GVector2 origin);

	virtual void setZIndex(float zIndex);
	virtual float getZIndex();

protected:
	GVector2	_position;
	GVector2	_scale;
	float		_rotate; // theo độ 0-360
	GVector2	_origin; // gốc của Transform, dùng để xoay, scale
	float		_zIndex;
};

#endif // !__TRANSFORMABLE_H__
