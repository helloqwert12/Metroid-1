#ifndef __BREAKABLEBLUEWALL_H__
#define __BREAKABLEBLUEWALL_H__

#include "define.h"
#include "BaseObject.h"
#include "Component.h"
#include "CollisionBody.h"
#include "Animation.h"
#include "StopWatch.h"

class BreakableBlueWall : public BaseObject
{
public:
	BreakableBlueWall(int x, int y);

	void init();
	void update(float deltatime);
	void draw(LPD3DXSPRITE, Viewport*);
	void release();

	void wasHit(int hitPoint);
	bool isDead();

	float checkCollision(BaseObject* object, float dt);

protected:
	Animation* _animation;
	map<string, Component*> _componentList;

	int _hitPoint;

	Sprite* _effect;
	Animation* _effectAnimation;
	StopWatch* _effectStopWatch;
};

#endif // !__BREAKABLEBLUEWALL_H__
