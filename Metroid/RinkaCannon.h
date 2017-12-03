#ifndef __RINKACANNON_H__
#define __RINKACANNON_H__

#include "define.h"
#include "BaseObject.h"
#include "Component.h"
#include "CollisionBody.h"
#include "Animation.h"
#include "StopWatch.h"
#include "QuadtreeNode.h"
#include <ctime>
#include "Rinka.h"

#define RINKA_APPEAR_TIME 3000
#define RINKA_MOVE_SPEED 30

class RinkaCannon : public BaseObject
{
public:
	RinkaCannon(int x, int y, int width, int height);

	void init();
	void update(float deltatime);
	void draw(LPD3DXSPRITE, Viewport*);
	void release();

	GVector2 getPosition();
	void setPosition(GVector2 position);

	RECT getBounding();

	void active();
	void deactive();
	bool isActive();

	float checkCollision(BaseObject* object, float dt);

protected:
	map<string, Component*> _componentList;

	// Do là empty object nên cần xác định bound thay vì lấy bound của Sprite
	RECT _bound;

	bool _isActive;

	StopWatch* _rinkaAppearStopWatch;
};

#endif // !__RINKACANNON_H__
