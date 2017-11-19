#include "IntroScene.h"
#include "SoundManager.h"
#include "PlayScene.h"

IntroScene::IntroScene()
{
}

IntroScene::~IntroScene()
{
}

bool IntroScene::init()
{
	__hook(&InputController::__eventkeyPressed, _input, &IntroScene::onKeyPressed);

	_background = SpriteManager::getInstance()->getSprite(eID::INTRO);
	_background->setPosition(256, 225);

	_pressStart = new TextSprite(eID::FONT, "PRESS START KEY", GVector2(145, 255));
	_pressStart->init();

	_thienAn = new TextSprite(eID::FONT, "THIEN AN - 15520008", GVector2(165, 350));
	_thienAn->init();
	_thienAn->setScale(1.25f);

	_huuDat = new TextSprite(eID::FONT, "HUU DAT  - 15520104", GVector2(165, 375));
	_huuDat->init();
	_huuDat->setScale(1.25f);

	_siDat = new TextSprite(eID::FONT, "SI DAT   - 15520105", GVector2(165, 400));
	_siDat->init();
	_siDat->setScale(1.25f);

	_leHuy = new TextSprite(eID::FONT, "LE HUY   - 15520312", GVector2(165, 425));
	_leHuy->init();
	_leHuy->setScale(1.25f);

	_flash = new StopWatch();
	_startGame = new StopWatch();

	_isPressed = false;
	_isDrawText = false;

	//SoundManager::getInstance()->PlayLoop(INTRO_SCENE);

	return true;
}

void IntroScene::updateInput(float deltatime)
{
}

void IntroScene::onKeyPressed(KeyEventArg* keyEvent)
{
	if (keyEvent->keyCode == DIK_Z)
	{
		_isPressed = true;
	}
}

void IntroScene::update(float dt)
{
	if (_isPressed)
	{
		if (_flash->isTimeLoop(120))
		{
			_isDrawText = !_isDrawText;
		}
		if (_startGame->isStopWatch(600))
		{
			SceneManager::getInstance()->replaceScene(new PlayScene());
		}
	}
}

void IntroScene::draw(LPD3DXSPRITE spriteHandle)
{
	_background->render(spriteHandle);

	if (!_isPressed)
	{
		_pressStart->draw(spriteHandle);
	}
	else
	{
		if (_isDrawText)
		{
			_pressStart->draw(spriteHandle);
		}
	}

	_thienAn->draw(spriteHandle);
	_huuDat->draw(spriteHandle);
	_siDat->draw(spriteHandle);
	_leHuy->draw(spriteHandle);
}

void IntroScene::release()
{
	//SoundManager::getInstance()->Stop(INTRO_SCENE);

	SAFE_DELETE(_pressStart);
	SAFE_DELETE(_background);
	SAFE_DELETE(_flash);
	SAFE_DELETE(_startGame);

	//if (_input != nullptr)
	//	__unhook(_input);
}
