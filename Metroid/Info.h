#ifndef __INFO_H__
#define __INFO_H__

#include "define.h"
#include "BaseObject.h"
#include "TextSprite.h"

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

	eID getWeapon();
	void setWeapon(eID id);

	int getMissileRocket();
	void setMissileRocke(int number);

private:
	Sprite* _iconLife;
	int _lifeNumber;
	TextSprite* _textLife;

	Sprite* _iconEnergy;
	int _energyNumber;
	TextSprite* _textEnergy;

	eID _weaponID;

	Sprite* _iconMissileRocket;
	int _missileRocketNumber;
	TextSprite* _textMissileRocket;
};

#endif // !__INFO_H__
