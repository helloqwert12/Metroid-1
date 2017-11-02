#include "IntroScene.h"
#include "SoundManager.h"

void IntroScene::updateInput(float deltatime)
{
	if (_input->isKeyDown(DIK_SPACE))
	{
		_ok = true;
	}
}

bool IntroScene::init()
{
	_introtable = SpriteManager::getInstance()->getSprite(eID::MAIN_MENU);
	_introtable->setPosition(256, 240);

	_gameTitle = new TextSprite(eID::FONTFULL, "METROID", GVector2(160, 150));
	_gameTitle->init();
	_gameTitle->setScale(4.0);

	_playOption = new TextSprite(eID::FONTFULL, "PRESS START KEY", GVector2(145, 250));
	_playOption->init();
	_playOption->setScale(2.0);

	_thienAn = new TextSprite(eID::FONTFULL, "THIEN AN - 15520008", GVector2(20, 300));
	_thienAn->init();
	_thienAn->setScale(2.0);

	_huuDat = new TextSprite(eID::FONTFULL, "HUU DAT  - 15520104", GVector2(20, 325));
	_huuDat->init();
	_huuDat->setScale(2.0);

	_siDat = new TextSprite(eID::FONTFULL, "SI DAT   - 15520105", GVector2(20, 350));
	_siDat->init();
	_siDat->setScale(2.0);

	_leHuy = new TextSprite(eID::FONTFULL, "LE HUY   - 15520312", GVector2(20, 375));
	_leHuy->init();
	_leHuy->setScale(2.0);

	_flash = new StopWatch();
	_access = new StopWatch();

	_ok = false;
	_draw = true;

	SoundManager::getInstance()->PlayLoop(INTRO_SCENE);

	return true;
}

void IntroScene::onKeyPressed(KeyEventArg* key_event)
{
}

void IntroScene::update(float dt)
{
	if (_ok)
	{
		if (_flash->isTimeLoop(120))
		{
			_draw = !_draw;
		}
		if (_access->isTimeLoop(800))
		{
			//SceneManager::getInstance()->replaceScene(new PlayScene());
		}
	}
}

void IntroScene::draw(LPD3DXSPRITE spriteHandle)
{
	_introtable->render(spriteHandle);
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

	_gameTitle->draw(spriteHandle);
	_thienAn->draw(spriteHandle);
	_huuDat->draw(spriteHandle);
	_siDat->draw(spriteHandle);
	_leHuy->draw(spriteHandle);
}

void IntroScene::release()
{
	SoundManager::getInstance()->Stop(INTRO_SCENE);

	SAFE_DELETE(_playOption);
	SAFE_DELETE(_introtable);
	SAFE_DELETE(_flash);
	SAFE_DELETE(_access);

	if (_input != nullptr)
		__unhook(_input);
}

IntroScene::IntroScene()
{
}

IntroScene::~IntroScene()
{
}
