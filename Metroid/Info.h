#ifndef __INFO_H__
#define __INFO_H__

#include "define.h"
#include "BaseObject.h"
#include "TextSprite.h"

#define GAP 10

class Info : public BaseObject
{
public:
	Info();
	~Info();

	virtual void init();
	virtual void update(float deltatime);
	virtual void draw(LPD3DXSPRITE, Viewport*);
	virtual void release();

	void setLife(int number);
	int getLife();

	void setEnergy(int number);
	int getEnergy();

	void setDebugAttack(string str);

private:
	Sprite* _iconLife;
	int _lifeNumber;
	TextSprite* _textLife;

	Sprite* _iconEnergy;
	int _energyNumber;
	TextSprite* _textEnergy;

	TextSprite* _debugAttack;
};

#endif // !__INFO_H__
