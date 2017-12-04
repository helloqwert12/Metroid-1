#ifndef __MOTHERBRAIN_H__
#define __MOTHERBRAIN_H__

#include "define.h"
#include "BaseObject.h"
#include "Component.h"
#include "CollisionBody.h"
#include "Animation.h"
#include "StopWatch.h"

class MotherBrain : public BaseObject
{
public:
	MotherBrain(int x, int y);

	void init();
	void update(float deltatime);
	void draw(LPD3DXSPRITE, Viewport*);
	void release();

	void wasHit(int hitPoint);
	bool isDead();

	float checkCollision(BaseObject* object, float dt);

protected:
	vector<Animation*> _animations;
	int _animationIndex;

	map<string, Component*> _componentList;

	int _hitPoint;

	Sprite* _effect;
	Animation* _effectAnimation;
	StopWatch* _effectStopWatch;

	StopWatch* _hitStopWatch;
	bool _startHitStopWatch;
};

#endif // !__MOTHERBRAIN_H__
