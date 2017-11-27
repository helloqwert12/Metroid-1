#ifndef __SINMOVEMENT_H__
#define __SINMOVEMENT_H__

#include "Sprite.h"
#include "Component.h"
#include <numeric>

// Chuyển động theo hàm Sin
class SinMovement : public Component
{
public:
	/*
		@amplitude: biên độ
		@frequency: tần số
		@refSprite: reference đến Sprite (để dùng hàm setPosition)
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

#endif // !__SINMOVEMENT_H__
