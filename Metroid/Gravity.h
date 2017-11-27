#ifndef __GRAVITY_H__
#define __GRAVITY_H__

#include "Component.h"
#include "Movement.h"

// Trạng thái của Gravity
enum eGravityStatus
{
	FALLING_DOWN,
	SHALLOWED
};

// Trọng lực của object, reference đến Movement component của object
class Gravity : public Component
{
public:
	/*
		@gravity: vector trọng lực của object, sẽ không đổi theo thời gian
		@movement: reference đến Movement của object (để dùng hàm setVelocity)
	*/
	Gravity(GVector2 gravity, Movement* movement);
	void update(float deltatime);

	eGravityStatus getStatus();
	void setStatus(eGravityStatus status);
	void setGravity(GVector2 gravity);

private:
	GVector2 _gravity;
	GVector2 _additionalVelocity;
	Movement* _refMovement;
	eGravityStatus _status;
};

#endif // !__GRAVITY_H__
