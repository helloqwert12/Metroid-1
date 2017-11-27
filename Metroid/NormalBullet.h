#ifndef __NORMALBULLET_H__
#define __NORMALBULLET_H__

#include "define.h"
#include "BaseObject.h"
#include "Component.h"
#include "Movement.h"
#include "CollisionBody.h"
#include "Animation.h"
#include "StopWatch.h"
#include "Weapon.h"

#define NORMAL_BULLET_SPEED 250

class NormalBullet : public Weapon
{
public:
	NormalBullet(int x, int y, eDirection direction, int bulletRange);

	void init() ;
	void update(float deltatime) ;
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

#endif // !__NORMALBULLET_H__
