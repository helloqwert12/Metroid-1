#ifndef __CHANGEMAPDIRECTION_H__
#define __CHANGEMAPDIRECTION_H__

#include "define.h"
#include "BaseObject.h"
#include "Component.h"
#include "CollisionBody.h"

class ChangeMapDirection : public BaseObject
{
public:
	ChangeMapDirection(int x, int y, int width, int height, eMapDirection mapDirection);

	void init();
	void update(float deltatime);
	void draw(LPD3DXSPRITE, Viewport*);
	void release();

	GVector2 getPosition();
	void setPosition(GVector2 position);

	RECT getBounding();
	eMapDirection getMapDirection();

private:
	map<string, Component*> _listComponent;

	// Do là empty object nên cần xác định bound thay vì lấy bound của Sprite
	RECT _bound;

	eMapDirection _mapDirection;
};

#endif // !__CHANGEMAPDIRECTION_H__
