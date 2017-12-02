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

	void init();
	void update(float deltatime);
	void draw(LPD3DXSPRITE, Viewport*);
	void release();

	int getLife();
	void setLife(int number);

	int getEnergy();
	void setEnergy(int number);

	int getMissileRocket();
	void setMissileRocket(int number);

	int getBulletRange();
	void setBulletRange(int number);

	eID getWeapon();
	void setWeapon(eID id);

	eID getBullet();
	void setBullet(eID id);

	bool hasMaruMari();
	void setMaruMari(bool flag);
	bool hasBomb();
	void setBomb(bool flag);
	bool hasVaria();
	void setVaria(bool flag);

	bool isAutoMoveViewport();
	void setAutoMoveViewport(bool flag);

	bool isStartMoveViewport();
	void startMoveViewport();

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

	// Khoảng bắn của viên đạn
	int _bulletRange;

	// Weapon hiện tại
	eID _weaponId;

	// Bullet hiện tại
	eID _bulletId;

	bool _hasMaruMari;
	bool _hasBomb;
	bool _hasVaria;

	bool _isAutoMoveViewport;
	bool _startMoveViewport;
};

#endif // !__INFO_H__
