#ifndef _ENERGYBALL_H_
#define _ENERGYBALL_H_

#include "define.h"
#include "BaseObject.h"
#include "IComponent.h"
#include "CollisionBody.h"
#include "Animation.h"
#include "StopWatch.h"

#define ENERGY_BALL_DESTROY_TIME 6000

class EnergyBall : public BaseObject
{
public:
	EnergyBall(int x, int y);

	void init();
	void update(float deltatime);
	void draw(LPD3DXSPRITE, Viewport*);
	void release();

	float checkCollision(BaseObject* object, float dt);

protected:
	Animation* _animation;
	map<string, IComponent*> _componentList;

	StopWatch* _destroyStopWatch;
};

#endif //!_ENERGYBALL_H_
