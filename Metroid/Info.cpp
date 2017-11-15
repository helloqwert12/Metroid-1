#include "Info.h"
#include "TextSprite.h"
#include <string>

Info::Info() : BaseObject(eID::LIFE_ICON)
{
	_iconLife = SpriteManager::getInstance()->getSprite(eID::LIFE_ICON);
	_iconLife->setScale(SCALE_FACTOR);
	_iconLife->setPosition(50, 25);

	_textLife = new TextSprite(eID::FONT, "", GVector2(0, 280));
	_textLife->init();
	_textLife->setScale(2.0);
	_textLife->setOrigin(VECTOR2ZERO);

	_iconEnergy = SpriteManager::getInstance()->getSprite(eID::ENEGY_ICON);
	_iconEnergy->setScale(SCALE_FACTOR);
	_iconEnergy->setPosition(50, 50);

	_textEnergy = new TextSprite(eID::FONT, "", GVector2(0, 280));
	_textEnergy->init();
	_textEnergy->setScale(2.0);
	_textEnergy->setOrigin(VECTOR2ZERO);

	_debugAttack = new TextSprite(eID::FONT, "", GVector2(0, 280));
	_debugAttack->init();
	_debugAttack->setScale(2.0);
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

	if (_lifeNumber <= 0)
	{
		_textLife->setString(" 00");
	}
	if (_lifeNumber > 0 && _lifeNumber < 10)
	{
		_textLife->setString(" 0" + to_string(_lifeNumber));
	}
	else if (_lifeNumber > 10 && _lifeNumber < 99)
	{
		_textLife->setString(" " + to_string(_lifeNumber));
	}

	_textEnergy->setPosition(GVector2(_iconEnergy->getPosition().x + GAP, _iconEnergy->getPosition().y + GAP / 1.4));
	
	if (_energyNumber <= 0)
	{
		_textEnergy->setString(" 00");
	}
	if (_energyNumber > 0 && _energyNumber < 10)
	{
		_textEnergy->setString(" 0" + to_string(_energyNumber));
	}
	else if (_energyNumber > 10 && _energyNumber < 99)
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

void Info::setLife(int number)
{
	_lifeNumber = number;
}

int Info::getLife()
{
	return _lifeNumber;
}

void Info::setEnergy(int number)
{
	_energyNumber = number;
}

int Info::getEnergy()
{
	return _energyNumber;
}

void Info::setDebugAttack(string str)
{
	_debugAttack->setString(str);
}
