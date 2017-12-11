#ifndef __ICEBULLET_H__
#define __ICEBULLET_H__

#include "define.h"
#include "Component.h"
#include "Movement.h"
#include "CollisionBody.h"
#include "Animation.h"
#include "StopWatch.h"
#include "Weapon.h"
#include "utils.h"

#define ICE_BULLET_SPEED 250

class IceBullet : public Weapon
{
public:
	IceBullet(int x, int y, eDirection direction, int bulletRange);

	void init();
	void update(float deltatime);
	void draw(LPD3DXSPRITE, Viewport*);
	void release();

	CollisionBody* getCollisionBody();

protected:
	map<string, Component*> _componentList;

	// Khoảng bắn của viên đạn
	int _bulletRange;

	// Vị trí ban đầu của weapon
	GVector2 _initPosition;
};

#endif // !__ICEBULLET_H__
