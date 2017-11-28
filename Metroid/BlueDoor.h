#ifndef __BLUEDOOR_H__
#define __BLUEDOOR_H__

#include "define.h"
#include "BaseObject.h"
#include "Component.h"
#include "Movement.h"
#include "CollisionBody.h"
#include "Animation.h"
#include "StopWatch.h"
#include "QuadtreeNode.h"

class BlueDoor : public BaseObject
{
public:
	BlueDoor(int x, int y);

	void init();
	void update(float deltatime);
	void draw(LPD3DXSPRITE, Viewport*);
	void release();

	void wasHit(int hitPoint);
	bool isDead();

	void close();
	void open();
	bool isClose();

	float checkCollision(BaseObject* object, float dt);

protected:
	Animation* _animation;
	map<string, Component*> _componentList;

	int _hitPoint;
	bool _isClose;

	Sprite* _effect;
	Animation* _effectAnimation;
};

#endif // !__BLUEDOOR_H__
