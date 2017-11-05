#ifndef __INFO_H__
#define __INFO_H__

#include "define.h"
#include "EmptyObject.h"
#include "TextSprite.h"

#define GAP 10

class Info : public EmptyObject
{
public:
	Info(GVector2 position, int number);
	~Info();

	virtual void init();
	virtual void update(float deltatime);
	virtual void draw(LPD3DXSPRITE, Viewport*);
	virtual void release();

	void setLifeNumber(int number);
	int getLifeNumber();

private:
	Sprite* _iconLife;
	TextSprite* _textLife;
	int _lifeNumber;
};

#endif // !__INFO_H__
