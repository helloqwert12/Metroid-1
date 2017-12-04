#ifndef __CANNONBULLET_H__
#define __CANNONBULLET_H__

#include "define.h"
#include "BaseObject.h"
#include "Component.h"
#include "Movement.h"
#include "CollisionBody.h"
#include "Animation.h"
#include "StopWatch.h"
#include "QuadtreeNode.h"
#include <ctime>

#define CANNON_BULLET_APPEAR_TIME 1000
#define CANNON_BULLET_MOVE_SPEED 200
#define CANNON_BULLET_RANGE 150

class CannonBullet : public BaseObject
{
public:
	// @cannonId ID của cannon (LEFT_CANNON, MIDDLE_CANNON, RIGHT_CANNON),'
	// dùng để set vận tốc và hướng sprite đạn
	CannonBullet(int x, int y, eID cannonId);

	void init();
	void update(float deltatime);
	void draw(LPD3DXSPRITE, Viewport*);
	void release();

	void wasHit(int hitPoint);
	bool isDead();

	void active();
	void deactive();
	bool isActive();

	float checkCollision(BaseObject* object, float dt);

protected:
	map<string, Component*> _componentList;

	int _hitPoint;
	bool _isActive;

	GVector2 _initPosition;
	GVector2 _velocity;

	Sprite* _effect;
	Animation* _effectAnimation;
	StopWatch* _effectStopWatch;

	StopWatch* _hitStopWatch;
	bool _startHitStopWatch;
};

#endif // !__CANNONBULLET_H__
