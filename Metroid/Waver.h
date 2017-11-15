#ifndef _WAVER_H
#define _WAVER_H

#include "define.h"
#include "BaseObject.h"
#include "IComponent.h"
#include "CollisionBody.h"
#include "Animation.h"
#include "StopWatch.h"
#include "QuadtreeNode.h"
#include <ctime>

#define WAVER_MOVE_SPEED 120

class Waver : public BaseObject
{
public:
	// @direct: hướng của object. TRUE sang phải, FALSE sang trái
	Waver(int x, int y, bool direct);

	void init() override;
	void update(float deltatime) override;
	void draw(LPD3DXSPRITE, Viewport*) override;
	void release() override;

	void wasHit(int hitpoint);
	bool isDead();

	void active(bool direct);
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
	bool _startHit;
};

#endif // !_WAVER_H
