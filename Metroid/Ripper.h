#ifndef __RIPPER_H__
#define __RIPPER_H__

#include "define.h"
#include "BaseObject.h"
#include "Component.h"
#include "Movement.h"
#include "CollisionBody.h"
#include "Animation.h"
#include "StopWatch.h"

#define RIPPER_MOVE_SPEED 50

class Ripper : public BaseObject
{
public:
	Ripper(int x, int y);

	void init();
	void update(float deltatime);
	void draw(LPD3DXSPRITE, Viewport*);
	void release();

	void wasHit(int hitPoint);
	bool isDead();

	void active();
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

#endif // !__RIPPER_H__
