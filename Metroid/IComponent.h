#ifndef __ICOMPONENT_H__
#define __ICOMPONENT_H__

#include "define.h"
#include "Sprite.h"
#include <numeric>
#include <map>
using namespace std;

class IComponent
{
public:
	virtual void update(float deltatime) = 0;
};


/*
	Chuyển động theo gia tốc và vận tốc.
	Khi không chuyển động thì gia tốc và vận tốc bằng 0
	Khi sử dụng:
		Khởi tạo bên trong init của object.
		Truyền refSprite = Sprite của object đó.
*/
class Movement : public IComponent
{
public:
	Movement(GVector2 accelerate, GVector2 velocicty, Sprite* refSprite);
	void update(float deltatime);

	void setAccelerate(GVector2 accelerate);
	void setVelocity(GVector2 velocicty);
	GVector2 getAccelerate();
	GVector2 getVelocity();

private:
	GVector2 _accelerate;
	GVector2 _velocity;
	Sprite* _refSprite;
};


enum eGravityStatus
{
	FALLING_DOWN,
	SHALLOWED
};

class Gravity : public IComponent
{
public:
	/* 
	Khởi tạo trọng lực của object, tham chiếu đến movement conponent của object
		@gravity: vector trọng lực của object, sẽ không đổi theo thời gian
		@movement: tham chiếu đến movement của object
	*/
	Gravity(GVector2 gravity, Movement* movement);
	void setStatus(eGravityStatus status);
	eGravityStatus getStatus();
	void update(float deltatime);
	void setGravity(GVector2 gravity);

private:
	GVector2 _gravity;
	GVector2 _additionalVelocity;
	Movement* _refMovement;
	eGravityStatus _status;
};


// Chuyển động hình sin
class SinMovement : public IComponent
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
	GVector2 _linearVelocity; // vận tốc tuyến tính (Aω*cos(φ))

	Sprite* _refSprite;
};

#endif // !__ICOMPONENT_H__
