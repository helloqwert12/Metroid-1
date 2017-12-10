#ifndef __RIDLEY_H__
#define __RIDLEY_H__

#include "define.h"
#include "BaseObject.h"
#include "Component.h"
#include "CollisionBody.h"
#include "StopWatch.h"
#include "QuadtreeNode.h"
#include "RidleyBullet.h"

#define RIDLEY_BULLET_APPEAR_TIME 500
#define RIDLEY_JUMP_TIME 2500
#define RIDLEY_JUMP_VELOCITY 300

class Ridley : public BaseObject
{
public:
	Ridley(int x, int y);

	void init();
	void update(float deltatime);
	void draw(LPD3DXSPRITE, Viewport*);
	void release();

	void wasHit(int hitPoint);
	bool isDead();

	void active();
	void deactive();
	bool isActive();

	void jump();
	void fall();
	void stand();

	float checkCollision(BaseObject* object, float dt);

protected:
	map<int, Animation*> _animations;
	map<string, Component*> _componentList;

	eStatus _currentAnimationIndex;

	int _hitPoint;
	bool _isActive;

	Sprite* _effect;
	Animation* _effectAnimation;
	StopWatch* _effectStopWatch;

	StopWatch* _hitStopWatch;
	bool _startHitStopWatch;

	StopWatch* _ridleyBulletAppearStopWatch;
	StopWatch* _ridleyJumpStopWatch;

	// Dùng để xét đã rời khỏi Wall đụng trước đó hay chưa
	BaseObject* _preWall;
};

#endif // !__RIDLEY_H__
