#ifndef __INFO_H__
#define __INFO_H__

#include "define.h"
#include "BaseObject.h"
#include "TextSprite.h"

#define BULLET_RANGE 80

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

	int getBulletRange();
	void setBulletRange(int number);

private:
	Sprite* _iconLife;
	int _lifeNumber;
	TextSprite* _textLife;

	Sprite* _iconEnergy;
	int _energyNumber;
	TextSprite* _textEnergy;

	Sprite* _iconMissileRocket;
	int _missileRocketNumber;
	TextSprite* _textMissileRocket;

	// Weapon hiện tại
	eID _weaponID;

	// Khoảng bắn của viên đạn
	int _bulletRange;
};

#endif // !__INFO_H__
