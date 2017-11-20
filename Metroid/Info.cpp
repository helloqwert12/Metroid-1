#include "Info.h"
#include "TextSprite.h"
#include <string>

Info::Info() : BaseObject(eID::LIFE_ICON)
{
	_iconLife = SpriteManager::getInstance()->getSprite(eID::LIFE_ICON);
	_iconLife->setPosition(50, 25);

	_textLife = new TextSprite(eID::FONT, "", GVector2(0, 280));
	_textLife->init();
	_textLife->setOrigin(VECTOR2ZERO);

	_iconEnergy = SpriteManager::getInstance()->getSprite(eID::ENERGY_ICON);
	_iconEnergy->setPosition(50, 50);

	_textEnergy = new TextSprite(eID::FONT, "", GVector2(0, 280));
	_textEnergy->init();
	_textEnergy->setOrigin(VECTOR2ZERO);

	_weaponID = NORMAL_BULLET;
	this->SetWeapon(_weaponID);

	_debugAttack = new TextSprite(eID::FONT, "", GVector2(0, 280));
	_debugAttack->init();
	_debugAttack->setOrigin(VECTOR2ZERO);
}

Info::~Info()
{
}

void Info::init()
{
}

void Info::update(float deltatime)
{
	_textLife->setPosition(GVector2(_iconLife->getPosition().x + GAP, _iconLife->getPosition().y + GAP / 1.4));

	if (_lifeNumber < 0)
	{
		_textLife->setString(" 00");
	}
	if (_lifeNumber >= 0 && _lifeNumber < 10)
	{
		_textLife->setString(" 0" + to_string(_lifeNumber));
	}
	else if (_lifeNumber >= 10 && _lifeNumber < 100)
	{
		_textLife->setString(" " + to_string(_lifeNumber));
	}

	_textEnergy->setPosition(GVector2(_iconEnergy->getPosition().x + GAP, _iconEnergy->getPosition().y + GAP / 1.4));
	
	if (_energyNumber < 0)
	{
		_textEnergy->setString(" 00");
	}
	if (_energyNumber >= 0 && _energyNumber < 10)
	{
		_textEnergy->setString(" 0" + to_string(_energyNumber));
	}
	else if (_energyNumber >= 10 && _energyNumber < 100)
	{
		_textEnergy->setString(" " + to_string(_energyNumber));
	}

	_debugAttack->setPosition(GVector2(_textLife->getPosition().x + GAP * 6, _iconLife->getPosition().y + GAP / 1.4));
}

void Info::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	_iconLife->render(spriteHandle);
	_textLife->draw(spriteHandle);

	_iconEnergy->render(spriteHandle);
	_textEnergy->draw(spriteHandle);

	_weaponSprite->render(spriteHandle);

	_debugAttack->draw(spriteHandle);
}

void Info::release()
{
	SAFE_DELETE(_iconLife);
	SAFE_DELETE(_textLife);
	SAFE_DELETE(_iconEnergy);
	SAFE_DELETE(_textEnergy);
	SAFE_DELETE(_debugAttack);
}

int Info::getLife()
{
	return _lifeNumber;
}

void Info::setLife(int number)
{
	_lifeNumber = number;
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

eID Info::GetWeapon()
{
	return _weaponID;
}

void Info::SetWeapon(eID id)
{
	_weaponID = id;

	switch (_weaponID)
	{
	case NORMAL_BULLET:
	{
		_weaponSprite = SpriteManager::getInstance()->getSprite(BULLET_EFFECT);
		_weaponSprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BULLET_EFFECT, "n_bullet_01"));
		_weaponSprite->setPosition(50, 75);
		break;
	}
	case ICE_BULLET:
	{
		_weaponSprite = SpriteManager::getInstance()->getSprite(BULLET_EFFECT);
		_weaponSprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BULLET_EFFECT, "i_bullet_01"));
		_weaponSprite->setPosition(50, 75);
		break;
	}
	case MISSILE_ROCKET:
	{
		_weaponSprite = SpriteManager::getInstance()->getSprite(BULLET_EFFECT);
		_weaponSprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BULLET_EFFECT, "missile_01"));
		_weaponSprite->setPosition(50, 75);
		break;
	}
	default:
		_weaponSprite = nullptr;
		break;
	}
}

void Info::setDebugAttack(string str)
{
	_debugAttack->setString(str);
}
