#ifndef __ZEB_H__
#define __ZEB_H__

#include "define.h"
#include "BaseObject.h"
#include "Component.h"
#include "Movement.h"
#include "CollisionBody.h"
#include "Animation.h"
#include "StopWatch.h"
#include "QuadtreeNode.h"
#include <ctime>

#define ZEB_MOVE_SPEED 300

class Zeb : public BaseObject
{
public:
	Zeb(int x, int y, GVector2 playerPosition);

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
	Animation* _animation;
	map<string, Component*> _componentList;

	int _hitPoint;
	bool _isActive;

	// Vị trí của Player, dùng để xác định thời điểm chuyển hướng
	GVector2 _playerPosition; 
	
	// Hướng bay về phía player
	// TRUE sang phải, FALSE sang trái
	bool _direction; 

	Sprite* _effect;
	Animation* _effectAnimation;
	StopWatch* _effectStopWatch;

	StopWatch* _hitStopWatch;
	bool _startHitStopWatch;
};

#endif // !__ZEB_H__
