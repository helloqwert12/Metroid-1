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

#define MOVE_SPEED 125
#define JUMP_VEL 450
#define GRAVITY 800
#define REVIVE_TIME 2000
#define PROTECT_TIME 3000

EVENT_RECEIVER
class Player : public BaseObject, public IControlable
{
public:
	Player(int life = 5);
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

	void setStatus(eStatus status) override;

	void removeGravity();
	void forceMoveRight();
	void unforceMoveRight();
	void forceMoveLeft();
	void unforceMoveLeft();
	void forceJump();
	void unforceJump();
	void unhookinputevent();

	void standing();
	void moveLeft();
	void moveRight();

	void moveUp();
	void moveDown();

	void jump();
	void sitDown();
	void falling();
	void hit();
	void revive();
	void die();

	float getMovingSpeed();

	RECT getBounding() override;

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

void safeCheckCollision(BaseObject* activeobj, BaseObject* passiveobj, float dt);

#endif // !__PLAYER_H__
