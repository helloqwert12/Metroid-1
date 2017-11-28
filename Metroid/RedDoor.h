#ifndef __REDDOOR_H__
#define __REDDOOR_H__

#include "define.h"
#include "BaseObject.h"
#include "Component.h"
#include "CollisionBody.h"
#include "Animation.h"
#include "StopWatch.h"

class RedDoor : public BaseObject
{
public:
	RedDoor(int x, int y);

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

#endif // !__REDDOOR_H__
