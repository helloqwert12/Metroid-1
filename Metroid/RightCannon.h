#ifndef __RIGHTCANNON_H__
#define __RIGHTCANNON_H__

#include "define.h"
#include "BaseObject.h"
#include "Component.h"
#include "CollisionBody.h"
#include "StopWatch.h"
#include "QuadtreeNode.h"
#include "CannonBullet.h"

class RightCannon : public BaseObject
{
public:
	RightCannon(int x, int y);

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

#endif // !__RIGHTCANNON_H__
