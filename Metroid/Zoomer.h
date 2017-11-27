#ifndef __ZOOMER_H__
#define __ZOOMER_H__

#include "define.h"
#include "BaseObject.h"
#include "Component.h"
#include "Movement.h"
#include "CollisionBody.h"
#include "Animation.h"
#include "StopWatch.h"
#include "QuadtreeNode.h"
#include <ctime>

#define ZOOMER_MOVE_SPEED 80

class Zoomer : public BaseObject
{
public:
	// @direction: hướng của object. TRUE sang phải, FALSE sang trái
	Zoomer(int x, int y);

	void init();
	void update(float deltatime);
	void draw(LPD3DXSPRITE, Viewport*);
	void release();

	void wasHit(int hitPoint);
	bool isDead();

	void active(bool direction);
	void deactive();
	bool isActive();

	float checkCollision(BaseObject* object, float dt);

protected:
	Animation* _animation;
	map<string, Component*> _componentList;

	int _hitPoint;
	bool _isActive;

	Sprite* _effect;
	Animation* _effectAnimation;
	StopWatch* _effectStopWatch;

	StopWatch* _hitStopWatch;
	bool _startHitStopWatch;

	BaseObject* _preWall;
	eDirection _preDirection;
};

#endif // !__ZOOMER_H__
