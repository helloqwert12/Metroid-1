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
	_background->setScale(2.0f);
	_background->setPosition(256, 225);

	_playOption = new TextSprite(eID::FONTFULL, "PRESS START KEY", GVector2(145, 255));
	_playOption->init();
	_playOption->setScale(2.0);

	_thienAn = new TextSprite(eID::FONTFULL, "THIEN AN - 15520008", GVector2(165, 350));
	_thienAn->init();
	_thienAn->setScale(1.25f);

	_huuDat = new TextSprite(eID::FONTFULL, "HUU DAT  - 15520104", GVector2(165, 375));
	_huuDat->init();
	_huuDat->setScale(1.25f);

	_siDat = new TextSprite(eID::FONTFULL, "SI DAT   - 15520105", GVector2(165, 400));
	_siDat->init();
	_siDat->setScale(1.25f);

	_leHuy = new TextSprite(eID::FONTFULL, "LE HUY   - 15520312", GVector2(165, 425));
	_leHuy->init();
	_leHuy->setScale(1.25f);

	_flash = new StopWatch();
	_access = new StopWatch();

	_ok = false;
	_draw = true;

	//SoundManager::getInstance()->PlayLoop(INTRO_SCENE);

	return true;
}

void IntroScene::updateInput(float deltatime)
{
}

void IntroScene::onKeyPressed(KeyEventArg* keyEvent)
{
	if (keyEvent->keycode == DIK_Z)
	{
		_ok = true;
	}
}

void IntroScene::update(float dt)
{
	if (_ok)
	{
		if (_flash->isTimeLoop(120))
		{
			_draw = !_draw;
		}
		if (_access->isStopWatch(800))
		{
			SceneManager::getInstance()->replaceScene(new PlayScene());
		}
	}
}

void IntroScene::draw(LPD3DXSPRITE spriteHandle)
{
	_background->render(spriteHandle);

	if (!_ok)
	{
		_playOption->draw(spriteHandle);
	}
	else
	{
		if (_draw)
		{
			_playOption->draw(spriteHandle);
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

	SAFE_DELETE(_playOption);
	SAFE_DELETE(_background);
	SAFE_DELETE(_flash);
	SAFE_DELETE(_access);

	//if (_input != nullptr)
	//	__unhook(_input);
}
