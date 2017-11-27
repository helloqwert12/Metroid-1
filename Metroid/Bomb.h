#ifndef __BOMB_H__
#define __BOMB_H__

#include "define.h"
#include "BaseObject.h"
#include "Component.h"
#include "Movement.h"
#include "CollisionBody.h"
#include "Animation.h"
#include "StopWatch.h"
#include "Weapon.h"

#define BOMB_EXPLODE_TIME 1000

class Bomb : public Weapon
{
public:
	Bomb(int x, int y);

	void init();
	void update(float deltatime);
	void draw(LPD3DXSPRITE, Viewport*);
	void release(); 
	
	CollisionBody* getCollisionBody();

protected:
	Animation* _animation;
	map<string, Component*> _componentList;

	Sprite* _effect;
	Animation* _effectAnimation;
	StopWatch* _effectStopWatch;

	bool _isExploded;
	StopWatch* _explodeStopWatch;

	void explode();
};

#endif // !__BOMB_H__
