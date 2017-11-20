#ifndef __NORMALBULLET_H__
#define __NORMALBULLET_H__

#include "define.h"
#include "BaseObject.h"
#include "IComponent.h"
#include "CollisionBody.h"
#include "Animation.h"
#include "StopWatch.h"
#include "Weapon.h"

#define NORMAL_BULLET_SPEED 250

class NormalBullet : public Weapon
{
public:
	NormalBullet(int x, int y, eDirection direction);

	void init() ;
	void update(float deltatime) ;
	void draw(LPD3DXSPRITE, Viewport*);
	void release();

protected:
	map<string, IComponent*> _componentList;
};

#endif // !__NORMALBULLET_H__
