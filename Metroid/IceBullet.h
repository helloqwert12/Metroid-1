#ifndef __ICEBULLET_H__
#define __ICEBULLET_H__

#include "define.h"
#include "BaseObject.h"
#include "IComponent.h"
#include "CollisionBody.h"
#include "Animation.h"
#include "StopWatch.h"
#include "Weapon.h"

#define ICE_BULLET_SPEED 250

class IceBullet : public Weapon
{
public:
	IceBullet(int x, int y, eDirection direction);

	void init();
	void update(float deltatime);
	void draw(LPD3DXSPRITE, Viewport*);
	void release();

protected:
	map<string, IComponent*> _componentList;
};

#endif // !__ICEBULLET_H__
