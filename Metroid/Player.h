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

#include "NormalBullet.h"
#include "IceBullet.h"
#include "MissileRocket.h"
#include "Bomb.h"

#include "Ripper.h"
#include "Waver.h"
#include "Skree.h"

#include "EnergyBall.h"

#define MOVE_SPEED 150
#define JUMP_VELOCITY 450
#define GRAVITY 600

#define PROTECT_TIME 1500
#define ATTACK_TIME 150

class Player : public BaseObject, public IControlable
{
public:
	Player();
	~Player();

	void init();
	void updateInput(float dt);
	void update(float deltatime);
	void draw(LPD3DXSPRITE spriteHandle, Viewport* viewport);
	void release();

	// Events
	void onKeyPressed(KeyEventArg* keyEvent);
	void onKeyReleased(KeyEventArg* keyEvent);

	void resetValues();

	void standing();
	void moveLeft();
	void moveRight();
	void jump();
	void falling();
	void beHit(eDirection direction);
	void die();
	void revive();

	float checkCollision(BaseObject* object, float dt);

	void setStatus(eStatus status);

	GVector2 getPosition();

	int getLifeNumber();

	RECT getBounding();

private:
	map<int, Animation*> _animations;
	map<string, IComponent*> _componentList;

	eStatus _currentAnimateIndex;
	Info* _info;

	float _movingSpeed;
	float _protectTime;

	vector<Weapon*> _listWeapon;

	bool _isRevive;
	GVector2 _revivePosition;

	// Từ status để gọi hành động
	void updateStatus(float dt);

	// Từ status để gọi attack
	void updateAttackStatus(float dt);

	// Từ status để chuyển animation
	void updateCurrentAnimateIndex();

	// Kiểm tra va chạm đạn, bomb
	bool checkWeaponCollision(BaseObject* object, eDirection & direction, float dt);

	GVector2 getVelocity();

	// Dùng để xét đã rời khỏi Wall đụng trước đó hay chưa
	BaseObject* preWall;

	// Dùng để giới hạn thời gian giữa 2 lần bắn đạn hoặc đặt bomb
	StopWatch* _attackStopWatch;
};

#endif // !__PLAYER_H__
