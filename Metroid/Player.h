#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "define.h"
#include "Animation.h"
#include "InputController.h"
#include "Viewport.h"
#include "StopWatch.h"
#include "BaseObject.h"
#include "IComponent.h"
#include "CollisionBody.h"
#include <list>
#include "Info.h"

#define MOVE_SPEED 150
#define JUMP_VELOCITY 520
#define GRAVITY 800
#define REVIVE_TIME 2000

[event_receiver(native)]
class Player : public BaseObject, public IControlable
{
public:
	Player(int life = 30);
	~Player();

	void init();
	void updateInput(float dt);
	void update(float deltatime);
	void draw(LPD3DXSPRITE spriteHandle, Viewport* viewport);
	void release();

	void onKeyPressed(KeyEventArg* key_event);
	void onKeyReleased(KeyEventArg* key_event);

	void onCollisionBegin(CollisionEventArg* collision_arg);
	void onCollisionEnd(CollisionEventArg* collision_arg);

	float checkCollision(BaseObject* object, float dt);
	void checkPosition();

	void setLifeNumber(int number);
	int getLifeNumber();

	void setStatus(eStatus status);

	// Player's Actions
	void standing();
	void moveLeft();
	void moveRight();
	void jump();
	void falling();
	void die();
	void revive();

	RECT getBounding();

private:
	map<int, Animation*> _animations;
	map<string, IComponent*> _componentList;

	float _movingSpeed;
	StopWatch* _stopWatch;

	eStatus _currentAnimateIndex;

	int _lifeNum;

	Info* _info;

	GVector2 getVelocity();

	void updateStatus(float dt);

	void updateCurrentAnimateIndex();

	void resetValues();

	BaseObject* preWall;
};

#endif // !__PLAYER_H__
