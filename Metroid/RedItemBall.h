#ifndef __REDITEMBALL_H__
#define __REDITEMBALL_H__

#include "define.h"
#include "BaseObject.h"
#include "Component.h"
#include "CollisionBody.h"
#include "Animation.h"
#include "StopWatch.h"
#include "QuadTreeNode.h"

class RedItemBall : public BaseObject
{
public:
	RedItemBall(int x, int y, eID itemId);

	void init();
	void update(float deltatime);
	void draw(LPD3DXSPRITE, Viewport*);
	void release();

	void wasHit(int hitPoint);
	bool isDead();

	eID getItemId();

	float checkCollision(BaseObject* object, float dt);

protected:
	Animation* _animation;
	map<string, Component*> _componentList;

	eID _itemId;
	int _hitPoint;

	Sprite* _effect;
	Animation* _effectAnimation;
};

#endif // !__REDITEMBALL_H__
