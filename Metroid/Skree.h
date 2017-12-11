#ifndef __SKREE_H__
#define __SKREE_H__

#include "define.h"
#include "BaseObject.h"
#include "Component.h"
#include "Movement.h"
#include "SinMovement.h"
#include "CollisionBody.h"
#include "Animation.h"
#include "StopWatch.h"
#include "QuadtreeNode.h"
#include <ctime>
#include "SkreeBullet.h"
#include "EnergyBall.h"

#define SKREE_MOVE_SPEED 300

class Skree : public BaseObject
{
public:
	Skree(int x, int y);

	void init();
	void update(float deltatime);
	void draw(LPD3DXSPRITE, Viewport*);
	void release();

	void wasHit(int hitPoint);
	bool isDead();

	void active();
	void deactive();
	bool isActive();

	GVector2 getVelocity();
	float checkCollision(BaseObject* object, float dt);

protected:
	Animation* _animation;
	map<string, Component*> _componentList;

	int _hitPoint;
	bool _isActive;
	bool _shootBullet;

	Sprite* _effect;
	Animation* _effectAnimation;
	StopWatch* _effectStopWatch;

	StopWatch* _hitStopWatch;
	bool _startHitStopWatch;
};

#endif // !__SKREE_H__
