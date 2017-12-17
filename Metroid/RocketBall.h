#ifndef __ROCKETBALL_H__
#define __ROCKETBALL_H__

#include "define.h"
#include "BaseObject.h"
#include "Component.h"
#include "CollisionBody.h"
#include "Animation.h"
#include "StopWatch.h"

#define ROCKET_BALL_DESTROY_TIME 6000

class RocketBall : public BaseObject
{
public:
	RocketBall(int x, int y);

	void init();
	void update(float deltatime);
	void draw(LPD3DXSPRITE, Viewport*);
	void release();

	float checkCollision(BaseObject* object, float dt);

protected:
	Animation* _animation;
	map<string, Component*> _componentList;

	StopWatch* _destroyStopWatch;
};

#endif // !__ROCKETBALL_H__
