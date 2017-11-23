#ifndef __WALL_H__
#define __WALL_H__

#include "define.h"
#include "BaseObject.h"
#include "Component.h"
#include "CollisionBody.h"

class Wall : public BaseObject
{
public:
	Wall(int x, int y, int width, int height);
	~Wall();

	void init();
	void update(float deltatime);
	void draw(LPD3DXSPRITE, Viewport*);
	void release();

	GVector2 getPosition();
	void setPosition(GVector2 position);

	RECT getBounding();

	float getPositionX();
	float getPositionY();
	void setPosition(GVector3 vector);
	void setPosition(float x, float y, float z);
	void setPosition(float x, float y);
	void setPositionX(float x);
	void setPositionY(float y);

	float getRotate();
	float getZIndex();

private:
	map<string, Component*> _listComponent;

	RECT _bound;
};

#endif // !__WALL_H__
