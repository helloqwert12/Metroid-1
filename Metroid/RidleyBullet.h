#ifndef __RIDLEYBULLET_H__
#define __RIDLEYBULLET_H__

#include "define.h"
#include "BaseObject.h"
#include "Component.h"
#include "Movement.h"
#include "CollisionBody.h"
#include "Animation.h"
#include "StopWatch.h"

#define RIDLEY_BULLET_MOVE_SPEED 80
#define RIDLEY_BULLET_RANGE 300

class RidleyBullet : public BaseObject
{
public:
	// @direction: hướng của object. TRUE sang phải, FALSE sang trái
	RidleyBullet(int x, int y, bool direction);

	void init();
	void update(float deltatime);
	void draw(LPD3DXSPRITE, Viewport*);
	void release();

	void wasHit(int hitPoint);
	bool isDead();

	void active();
	void deactive();
	bool isActive();

	float checkCollision(BaseObject* object, float dt);

protected:
	Animation* _animation;
	map<string, Component*> _componentList;

	int _hitPoint;
	bool _isActive;

	GVector2 _initPosition;
	GVector2 _accelerate;
	GVector2 _velocity;

	Sprite* _effect;
	Animation* _effectAnimation;
	StopWatch* _effectStopWatch;

	StopWatch* _hitStopWatch;
	bool _startHitStopWatch;
};

#endif // !__RIDLEYBULLET_H__
