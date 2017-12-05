#ifndef __MIDDLECANNON_H__
#define __MIDDLECANNON_H__

#include "define.h"
#include "BaseObject.h"
#include "Component.h"
#include "CollisionBody.h"
#include "Animation.h"
#include "StopWatch.h"
#include "QuadtreeNode.h"
#include <ctime>
#include "CannonBullet.h"

class MiddleCannon : public BaseObject
{
public:
	MiddleCannon(int x, int y);

	void init();
	void update(float deltatime);
	void draw(LPD3DXSPRITE, Viewport*);
	void release();

	void active();
	void deactive();
	bool isActive();

	float checkCollision(BaseObject* object, float dt);

protected:
	map<string, Component*> _componentList;

	int _spriteIndex;
	bool _isActive;

	StopWatch* _cannonBulletAppearStopWatch;
};

#endif // !__MIDDLECANNON_H__
