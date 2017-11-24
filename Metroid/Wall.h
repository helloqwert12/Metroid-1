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

	void init();
	void update(float deltatime);
	void draw(LPD3DXSPRITE, Viewport*);
	void release();

	GVector2 getPosition();
	void setPosition(GVector2 position);

	RECT getBounding();

private:
	map<string, Component*> _listComponent;

	// Do là empty object nên cần xác định bound thay vì lấy bound của Sprite
	RECT _bound;
};

#endif // !__WALL_H__
