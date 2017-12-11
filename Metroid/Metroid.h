#ifndef __METROID_H__
#define __METROID_H__

#include "define.h"
#include "BaseObject.h"
#include "Component.h"
#include "Movement.h"
#include "SinMovement.h"
#include "CollisionBody.h"
#include "Animation.h"
#include "StopWatch.h"

#define METROID_MOVE_SPEED 80

class Metroid : public BaseObject
{
public:
	// @direction: hướng của object. TRUE sang phải, FALSE sang trái
	Metroid(int x, int y, bool direction);

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
};

#endif // !__METROID_H__
