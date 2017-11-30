#ifndef __ZEBPIPE_H__
#define __ZEBPIPE_H__

#include "define.h"
#include "BaseObject.h"
#include "Component.h"
#include "CollisionBody.h"
#include "Animation.h"
#include "StopWatch.h"
#include "QuadtreeNode.h"
#include <ctime>
#include "Zeb.h"

#define ZEB_APPEAR_TIME 3000

class ZebPipe : public BaseObject
{
public:
	ZebPipe(int x, int y, int width, int height);

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

	StopWatch* _zebAppearStopWatch;
};

#endif // !__ZEBPIPE_H__
