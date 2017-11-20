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

	int getLife();
	void setLife(int number);

	int getEnergy();
	void setEnergy(int number);

	eID GetWeapon();
	void SetWeapon(eID id);

	void setDebugAttack(string str);

private:
	Sprite* _iconLife;
	int _lifeNumber;
	TextSprite* _textLife;

	Sprite* _iconEnergy;
	int _energyNumber;
	TextSprite* _textEnergy;

	eID _weaponID;
	Sprite* _weaponSprite;

	TextSprite* _debugAttack;
};

#endif // !__INFO_H__
