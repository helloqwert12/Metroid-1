#ifndef __RIPPER_H__
#define __RIPPER_H__

#include "define.h"
#include "BaseObject.h"
#include "IComponent.h"
#include "CollisionBody.h"
#include "Animation.h"
#include "StopWatch.h"
#include "QuadtreeNode.h"
#include <ctime>

#define RIPPER_MOVE_SPEED 50

class Ripper : public BaseObject
{
public:
	// @direction: hướng của object. TRUE sang phải, FALSE sang trái
	Ripper(int x, int y, bool direction);

	void init();
	void update(float deltatime);
	void draw(LPD3DXSPRITE, Viewport*);
	void release();

	void wasHit(int hitPoint);
	bool isDead();

	float checkCollision(BaseObject* object, float dt);

protected:
	Animation* _animation;
	map<string, IComponent*> _componentList;

	int _hitPoint;

	Sprite* _effect;
	Animation* _effectAnimation;
	StopWatch* _effectStopWatch;

	StopWatch* _hitStopWatch;
	bool _startHitStopWatch;
};

#endif // !__RIPPER_H__
