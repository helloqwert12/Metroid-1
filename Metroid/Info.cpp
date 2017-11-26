#include "Info.h"
#include "TextSprite.h"
#include <string>

Info::Info() : BaseObject(eID::INFO)
{
	// Info dùng tọa độ top-left
	_iconLife = SpriteManager::getInstance()->getSprite(eID::LIFE_ICON);
	_iconLife->setPosition(50, 25);

	_textLife = new TextSprite("", GVector2(0, 0));
	_textLife->init();

	_iconEnergy = SpriteManager::getInstance()->getSprite(eID::ENERGY_ICON);
	_iconEnergy->setPosition(50, 50);

	_textEnergy = new TextSprite("", GVector2(0, 0));
	_textEnergy->init();

	_missileRocketNumber = 5;
	_iconMissileRocket = SpriteManager::getInstance()->getSprite(BULLET_EFFECT);
	_iconMissileRocket->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BULLET_EFFECT, "missile_rocket_01"));
	_iconMissileRocket->setPosition(50, 75);

	_textMissileRocket = new TextSprite("", GVector2(0, 0));
	_textMissileRocket->init();
}

Info::~Info()
{
}

void Info::init()
{
	_weaponId = NORMAL_BULLET;
	_bulletId = NORMAL_BULLET;

	this->setWeapon(_weaponId);
	_bulletRange = BULLET_RANGE;

	_hasMaruMari = false;
	_hasBomb = false;
	_hasVaria = false;
}

void Info::update(float deltatime)
{
	_textLife->setPosition(GVector2(_iconLife->getPosition().x + 35, _iconLife->getPosition().y));

	if (_lifeNumber < 0)
	{
		_textLife->setText("00");
	}
	if (_lifeNumber >= 0 && _lifeNumber < 10)
	{
		_textLife->setText("0" + to_string(_lifeNumber));
	}
	else if (_lifeNumber >= 10 && _lifeNumber < 100)
	{
		_textLife->setText("" + to_string(_lifeNumber));
	}

	_textEnergy->setPosition(GVector2(_iconEnergy->getPosition().x + 35, _iconEnergy->getPosition().y));
	
	if (_energyNumber < 0)
	{
		_textEnergy->setText("00");
	}
	if (_energyNumber >= 0 && _energyNumber < 10)
	{
		_textEnergy->setText("0" + to_string(_energyNumber));
	}
	else if (_energyNumber >= 10 && _energyNumber < 100)
	{
		_textEnergy->setText("" + to_string(_energyNumber));
	}

	_textMissileRocket->setPosition(GVector2(_iconMissileRocket->getPosition().x + 35, _iconMissileRocket->getPosition().y));

	if (_missileRocketNumber < 0)
	{
		_textMissileRocket->setText(" 00");
	}
	if (_missileRocketNumber >= 0 && _missileRocketNumber < 10)
	{
		_textMissileRocket->setText("0" + to_string(_missileRocketNumber));
	}
	else if (_missileRocketNumber >= 10 && _missileRocketNumber < 100)
	{
		_textMissileRocket->setText("" + to_string(_missileRocketNumber));
	}
}

void Info::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	_iconLife->render(spriteHandle);
	_textLife->draw(spriteHandle);

	_iconEnergy->render(spriteHandle);
	_textEnergy->draw(spriteHandle);

	if (_missileRocketNumber > 0)
	{
		_iconMissileRocket->render(spriteHandle);
		_textMissileRocket->draw(spriteHandle);
	}
}

void Info::release()
{
	SAFE_DELETE(_iconLife);
	SAFE_DELETE(_textLife);
	SAFE_DELETE(_iconEnergy);
	SAFE_DELETE(_textEnergy);
	SAFE_DELETE(_iconMissileRocket);
}

int Info::getLife()
{
	return _lifeNumber;
}

void Info::setLife(int number)
{
	_lifeNumber = number;

	if (_lifeNumber >= 100)
		_lifeNumber = 99;
}

int Info::getEnergy()
{
	return _energyNumber;
}

void Info::setEnergy(int number)
{
	_energyNumber = number;

	if (_energyNumber >= 100)
		_energyNumber = 99;
}

int Info::getMissileRocket()
{
	return _missileRocketNumber;
}

void Info::setMissileRocket(int number)
{
	_missileRocketNumber = number;

	if (_missileRocketNumber >= 100)
		_missileRocketNumber = 99;
}

int Info::getBulletRange()
{
	return _bulletRange;
}

void Info::setBulletRange(int number)
{
	_bulletRange = number;
}

eID Info::getWeapon()
{
	return _weaponId;
}

void Info::setWeapon(eID id)
{
	_weaponId = id;
}

eID Info::getBullet()
{
	return _bulletId;
}

void Info::setBullet(eID id)
{
	_bulletId = id;
}

bool Info::hasMaruMari()
{
	return _hasMaruMari;
}

void Info::setMaruMari(bool flag)
{
	_hasMaruMari = flag;
}

bool Info::hasBomb()
{
	return _hasBomb;
}

void Info::setBomb(bool flag)
{
	_hasBomb = flag;
}

bool Info::hasVaria()
{
	return _hasVaria;
}

void Info::setVaria(bool flag)
{
	_hasVaria = flag;
}
