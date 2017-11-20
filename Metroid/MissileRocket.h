#ifndef __MISSILEROCKET_H__
#define __MISSILEROCKET_H__

#include "define.h"
#include "BaseObject.h"
#include "IComponent.h"
#include "CollisionBody.h"
#include "Animation.h"
#include "StopWatch.h"
#include "Weapon.h"

#define MISSILE_ROCKET_SPEED 250

class MissileRocket : public Weapon
{
public:
	MissileRocket(int x, int y, bool direct);

	void init();
	void update(float deltatime);
	void draw(LPD3DXSPRITE, Viewport*);
	void release();

protected:
	map<string, IComponent*> _componentList;
};

#endif // !__MISSILEROCKET_H__
