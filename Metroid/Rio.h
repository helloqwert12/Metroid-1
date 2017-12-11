#ifndef __RIO_H__
#define __RIO_H__

#include "define.h"
#include "BaseObject.h"
#include "Component.h"
#include "Movement.h"
#include "SinMovement.h"
#include "CollisionBody.h"
#include "Animation.h"
#include "StopWatch.h"
#include "QuadtreeNode.h"
#include <ctime>
#include "EnergyBall.h"

#define RIO_MOVE_SPEED 100

class Rio : public BaseObject
{
public:
	// @direction: hướng của object. TRUE sang phải, FALSE sang trái
	Rio(int x, int y, bool direction);

	void init();
	void update(float deltatime);
	void draw(LPD3DXSPRITE, Viewport*);
	void release();

	void wasHit(int hitPoint);
	bool isDead();

	void active(bool direction);
	void deactive();
	bool isActive();

	GVector2 getVelocity();
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
};

#endif // !__RIO_H__
