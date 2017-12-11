#ifndef __RINKA_H__
#define __RINKA_H__

#include "define.h"
#include "BaseObject.h"
#include "Component.h"
#include "Movement.h"
#include "CollisionBody.h"
#include "Animation.h"
#include "StopWatch.h"
#include "utils.h"

#define RINKA_RANGE 300

class Rinka : public BaseObject
{
public:
	// @velocity: vận tốc ban đầu, dùng để xác định hướng di chuyển
	Rinka(int x, int y, GVector2 velocity);

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
	GVector2 _velocity;

	Sprite* _effect;
	Animation* _effectAnimation;
	StopWatch* _effectStopWatch;

	StopWatch* _hitStopWatch;
	bool _startHitStopWatch;
};

#endif // !__RINKA_H__
