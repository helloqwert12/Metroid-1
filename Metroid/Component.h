#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "define.h"
#include "Sprite.h"
#include <numeric>
using namespace std;

class Component
{
public:
	virtual void update(float deltatime) = 0;
};


// Chuyển động theo gia tốc và vận tốc.
class Movement : public Component
{
public:
	/*
		@accelerate: gia tốc
		@velocity: vận tốc
		@refSprite: reference đến Sprite (để dùng hàm setPosition)
	*/
	Movement(GVector2 accelerate, GVector2 velocicty, Sprite* refSprite);
	void update(float deltatime);

	GVector2 getAccelerate();
	void setAccelerate(GVector2 accelerate);
	GVector2 getVelocity();
	void setVelocity(GVector2 velocicty);

private:
	GVector2 _accelerate;
	GVector2 _velocity;
	Sprite* _refSprite;
};


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


// Chuyển động theo hàm Sin
class SinMovement : public Component
{
public:
	/*
		@amplitude: biên độ
		@frequency: tần số
	*/
	SinMovement(GVector2 amplitude, float frequency, Sprite* refSprite);
	void update(float deltatime);

	void setAmplitude(GVector2 amplitude);
	void setFrequency(float frequency);

private:
	float _radian; // góc xoay (φ) biến thiên theo thời gian
	float _radianVelocity; // vận tốc góc (ω)

	GVector2 _amplitude; // biên độ	(A)
	GVector2 _linearVelocity; // vận tốc tuyến tính (A * ω * cos(φ))

	Sprite* _refSprite;
};

#endif // !__COMPONENT_H__
