#ifndef __WAVER_H__
#define __WAVER_H__

#include "define.h"
#include "BaseObject.h"
#include "IComponent.h"
#include "CollisionBody.h"
#include "Animation.h"
#include "StopWatch.h"
#include "QuadtreeNode.h"
#include <ctime>

#define WAVER_MOVE_SPEED 80

class Waver : public BaseObject
{
public:
	// @direction: hướng của object. TRUE sang phải, FALSE sang trái
	Waver(int x, int y, bool direction);

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
	map<string, IComponent*> _componentList;

	int _hitPoint;
	bool _isActive;

	Sprite* _effect;
	Animation* _effectAnimation;
	StopWatch* _effectStopWatch;

	StopWatch* _hitStopWatch;
	bool _startHitStopWatch;
};

#endif // !__WAVER_H__
