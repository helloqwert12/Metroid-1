#include "VictoryScene.h"
#include "SoundManager.h"
#include "IntroScene.h"

VictoryScene::VictoryScene()
{
}

VictoryScene::~VictoryScene()
{
}

bool VictoryScene::init()
{
	__hook(&InputController::__eventkeyPressed, _input, &VictoryScene::onKeyPressed);

	_sprite = SpriteManager::getInstance()->getSprite(eID::PLAYER_VICTORY);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::PLAYER_VICTORY, "samus_aran_01"));
	_sprite->setScale(2.5f);
	_sprite->setPosition(250, 350);

	_samusAnimations.push_back(new Animation(_sprite, 0.07f));
	_samusAnimations.push_back(new Animation(_sprite, 0.07f));
	_samusAnimations.push_back(new Animation(_sprite, 0.2f));
	_samusAnimations.push_back(new Animation(_sprite, 0.2f, false)); // Disapear animation

	_samusAnimations[0]->addFrameRect(PLAYER_VICTORY, "samus_aran_01", "samus_aran_02", "samus_aran_03",
												"samus_aran_04", "samus_aran_05", "samus_aran_06", 
												"samus_aran_07", "samus_aran_08", "samus_aran_09", NULL);

	_samusAnimations[1]->addFrameRect(PLAYER_VICTORY, "samus_suitless_01", "samus_suitless_02", "samus_suitless_03",
												"samus_suitless_04", "samus_suitless_05", "samus_suitless_06",
												"samus_suitless_07", "samus_suitless_08", "samus_suitless_09", NULL);

	_samusAnimations[2]->addFrameRect(PLAYER_VICTORY, "samus_goodbye_01", "samus_goodbye_02", NULL);
	_samusAnimations[3]->addFrameRect(PLAYER_VICTORY, "samus_disappear_01", "samus_disappear_02", NULL);

	_animationIndex = 0;

	_text.push_back(new TextSprite("GREAT !!", GVector2(200, 50)));
	_text[0]->init();

	_text.push_back(new TextSprite("YOU FULFILED YOUR MISSION.", GVector2(20, 90)));
	_text[1]->init();

	_text.push_back(new TextSprite("IT WILL REVIVE PEACE IN SPACE.", GVector2(20, 130)));
	_text[2]->init();

	_text.push_back(new TextSprite("BUT IT MAY BE INVADED BY", GVector2(20, 170)));
	_text[3]->init();

	_text.push_back(new TextSprite("THE OTHER METROID.", GVector2(20, 210)));
	_text[4]->init();

	_text.push_back(new TextSprite("PRAY FOR A TRUE PEACE IN SPACE!", GVector2(20, 250)));
	_text[5]->init();

	_changeAnimation = new StopWatch();
	_startGame = new StopWatch();
	_isPressed = false;

	return true;
}

void VictoryScene::updateInput(float deltatime)
{
}

void VictoryScene::onKeyPressed(KeyEventArg* keyEvent)
{
	if (keyEvent->keyCode == DIK_Z)
		_isPressed = true;
}

void VictoryScene::update(float dt)
{
	if (_changeAnimation->isStopWatch(3000))
	{
		if (_animationIndex < 3)
		{
			_animationIndex++;
			_changeAnimation->restart();
		}
	}

	_samusAnimations[_animationIndex]->update(dt);

	if (_isPressed)
	{
		if (_startGame->isStopWatch(600))
			SceneManager::getInstance()->replaceScene(new IntroScene());
	}
}

void VictoryScene::draw(LPD3DXSPRITE spriteHandle)
{
	if (_samusAnimations[_animationIndex]->isAnimate())
		_samusAnimations[_animationIndex]->draw(spriteHandle);

	for (auto text : _text)
		text->draw(spriteHandle);
}

void VictoryScene::release()
{
	for (auto it = _samusAnimations.begin(); it != _samusAnimations.end(); it++)
	{
		SAFE_DELETE(*it);
	}

	for (auto it = _text.begin(); it != _text.end(); it++)
	{
		SAFE_DELETE(*it);
	}

	SAFE_DELETE(_changeAnimation);
	SAFE_DELETE(_startGame);
}
