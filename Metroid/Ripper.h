#ifndef _RIPPER_H
#define _RIPPER_H

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
	// @direct: hướng của object. TRUE sang phải, FALSE sang trái
	Ripper(int x, int y, bool direct);

	void init() override;
	void update(float deltatime) override;
	void draw(LPD3DXSPRITE, Viewport*) override;
	void release() override;

	void wasHit(int hitpoint);
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
	bool _startHit;
};

#endif // !_RIPPER_H
