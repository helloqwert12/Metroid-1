#ifndef __MISSILEROCKET_H__
#define __MISSILEROCKET_H__

#include "define.h"
#include "Component.h"
#include "Movement.h"
#include "CollisionBody.h"
#include "Animation.h"
#include "StopWatch.h"
#include "Weapon.h"
#include "utils.h"

#define MISSILE_ROCKET_SPEED 300

class MissileRocket : public Weapon
{
public:
	MissileRocket(int x, int y, eDirection direction);

	void init();
	void update(float deltatime);
	void draw(LPD3DXSPRITE, Viewport*);
	void release();

	GVector2 getVelocity();
	CollisionBody* getCollisionBody();

protected:
	map<string, Component*> _componentList;
};

#endif // !__MISSILEROCKET_H__
