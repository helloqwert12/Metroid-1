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
#include "Info.h"
#include "Ripper.h"
#include "Waver.h"

#define MOVE_SPEED 150
#define JUMP_VELOCITY 450
#define GRAVITY 600
#define PROTECT_TIME 2000

class Player : public BaseObject, public IControlable
{
public:
	Player(int life = 3);
	~Player();

	void init();
	void updateInput(float dt);
	void update(float deltatime);
	void draw(LPD3DXSPRITE spriteHandle, Viewport* viewport);
	void release();

	// Events
	void onKeyPressed(KeyEventArg* keyEvent);
	void onKeyReleased(KeyEventArg* keyEvent);

	void standing();
	void moveLeft();
	void moveRight();
	void jump();
	void falling();
	void shoot();
	void bomb();
	void beHit(eDirection direction);
	void die();

	void checkPosition();
	float checkCollision(BaseObject* object, float dt);

	GVector2 getPosition();

	int getLifeNumber();

	void setStatus(eStatus status);

	RECT getBounding();

	void resetValues();

private:
	map<int, Animation*> _animations;
	map<string, IComponent*> _componentList;

	float _movingSpeed;
	StopWatch* _stopWatch;

	eStatus _currentAnimateIndex;

	Info* _info;

	float _protectTime;

	GVector2 getVelocity();

	void updateStatus(float dt);

	void updateCurrentAnimateIndex();

	// Dùng để xét đã rời khỏi Wall đụng trước đó hay chưa
	BaseObject* preWall;
};

#endif // !__PLAYER_H__
