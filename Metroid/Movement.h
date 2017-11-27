#ifndef __MOVEMENT_H__
#define __MOVEMENT_H__

#include "Sprite.h"
#include "Component.h"

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

#endif // !__MOVEMENT_H__
