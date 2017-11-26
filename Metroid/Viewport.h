#ifndef __VIEWPORT_H__
#define __VIEWPORT_H__

#include "define.h"

class Viewport
{
public:
	Viewport(float x, float y, float width, float height);
	~Viewport();

	void setPositionWorld(GVector2 position);
	GVector2 getPositionWorld();

	float getWidth();
	float getHeight();

	// Chuyển từ tọa độ world (x, y) sang tọa độ trong viewport (top-left)
	GVector3 getPositionInViewport(GVector3* position);

	// Lấy kích thước HCN của viewport, tính trong world (x, y)
	RECT getBounding();

private:
	GVector2 _positionWorld;
	float _width;
	float _height;
};

#endif // !__VIEWPORT_H__
