#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "define.h"
#include "Animation.h"
#include "InputController.h"
#include "Viewport.h"
#include "StopWatch.h"
#include "BaseObject.h"
#include "Component.h"
#include "Movement.h"
#include "Gravity.h"
#include "CollisionBody.h"
#include "Info.h"

#include "ChangeMapDirection.h"

#include "BlueDoor.h"
#include "RedDoor.h"
#include "BreakableBlueWall.h"
#include "BreakableRedWall.h"
#include "BlueItemBall.h"
#include "RedItemBall.h"

#include "NormalBullet.h"
#include "IceBullet.h"
#include "MissileRocket.h"
#include "Bomb.h"

#include "SkreeBullet.h"
#include "Ripper.h"
#include "Waver.h"
#include "Skree.h"
#include "Mellow.h"
#include "Rio.h"
#include "Zeb.h"
#include "ZebPipe.h"
#include "Zoomer.h"

#include "Zeebetite.h"
#include "Metroid.h"
#include "MotherBrain.h"
#include "Rinka.h"
#include "RinkaCannon.h"
#include "CannonBullet.h"
#include "LeftCannon.h"
#include "MiddleCannon.h"
#include "RightCannon.h"

#include "RidleyBullet.h"
#include "Ridley.h"

#include "EnergyTank.h"
#include "EnergyBall.h"
#include "MaruMari.h"
#include "LongBeam.h"
#include "IceBeam.h"
#include "MissileRocketBall.h"
#include "BombBall.h"
#include "Varia.h"

#define MOVE_SPEED 150
#define MOVE_SPEED_IN_FIRE 75
#define JUMP_VELOCITY 450
#define GRAVITY 600

#define PROTECT_TIME 1500
#define BULLET_ATTACK_TIME 200
#define MISSILE_ROCKET_ATTACK_TIME 350
#define BOMB_ATTACK_TIME 400

class Player : public BaseObject, public Controlable
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

	void stand();
	void moveLeft();
	void moveRight();
	void jump();
	void fall();
	void beHit(eDirection direction);
	void takeDamage(int number);
	void die();
	void revive();

	Info* getInfo();
	int getLifeNumber();
	RECT getBounding();

	float checkCollision(BaseObject* object, float dt);

private:
	map<int, Animation*> _animations;
	map<string, Component*> _componentList;

	eStatus _currentAnimationIndex;
	Info* _info;

	float _moveSpeed;
	float _protectTime;

	vector<Weapon*> _listWeapon;

	// List các enemy dính vào với player (Metroid)
	vector<BaseObject*> _stickyObjects;

	bool _isRevive;
	GVector2 _revivePosition;

	// Bị hút máu
	bool _isBeingBloodSucking;

	// Từ status để gọi hành động
	void updateStatus(float dt);

	// Từ status để gọi attack
	void updateAttackStatus(float dt);

	// Từ status để chuyển animation
	void updateCurrentAnimateIndex();

	// Kiểm tra va chạm weapon (đạn, bomb)
	bool checkWeaponCollision(BaseObject* object, eDirection& direction, eID& weaponID, float dt);

	GVector2 getVelocity();

	// Dùng để xét đã rời khỏi Wall đụng trước đó hay chưa
	BaseObject* _preWall;

	// Dùng để xét đã rời khỏi Fire đụng trước đó hay chưa
	BaseObject* _preFire;

	// Dùng để giới hạn thời gian giữa 2 lần bắn đạn hoặc đặt bomb
	StopWatch* _attackStopWatch;

	StopWatch* _bloodSuckingStopWatch;
};

#endif // !__PLAYER_H__
