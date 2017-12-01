#include "GameOverScene.h"
#include "SoundManager.h"
#include "PlayScene.h"

GameOverScene::GameOverScene()
{
}

GameOverScene::~GameOverScene()
{
}

bool GameOverScene::init()
{
	__hook(&InputController::__eventkeyPressed, _input, &GameOverScene::onKeyPressed);

	_gameOver = new TextSprite("GAME OVER", GVector2(175, 150));
	_gameOver->init();
	_gameOver->setScale(2.5f);

	_pressStart = new TextSprite("PRESS START KEY TO PLAY AGAIN", GVector2(90, 255));
	_pressStart->init();
	_pressStart->setScale(1.5f);

	_pressEscape = new TextSprite("PRESS ESCAPE KEY TO QUIT", GVector2(120, 275));
	_pressEscape->init();
	_pressEscape->setScale(1.5f);

	_flash = new StopWatch();
	_startGame = new StopWatch();

	_isPressed = false;
	_isDrawText = false;

	return true;
}

void GameOverScene::updateInput(float deltatime)
{
}

void GameOverScene::onKeyPressed(KeyEventArg* keyEvent)
{
	if (keyEvent->keyCode == DIK_Z)
	{
		_isPressed = true;
	}
}

void GameOverScene::update(float dt)
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

void GameOverScene::draw(LPD3DXSPRITE spriteHandle)
{
	_gameOver->draw(spriteHandle);

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

	_pressEscape->draw(spriteHandle);
}

void GameOverScene::release()
{
	SAFE_DELETE(_gameOver);
	SAFE_DELETE(_pressStart);
	SAFE_DELETE(_pressEscape);
	SAFE_DELETE(_flash);
	SAFE_DELETE(_startGame);
}
