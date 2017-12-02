#include "GameOverScene.h"
#include "SoundManager.h"
#include "IntroScene.h"
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
	
	_choiceIcon = SpriteManager::getInstance()->getSprite(eID::BULLET_EFFECT);
	_choiceIcon->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BULLET_EFFECT, "missile_rocket_01"));
	_choiceIcon->setPosition(130, 250);

	_gameOver = new TextSprite("GAME OVER", GVector2(175, 150));
	_gameOver->init();
	_gameOver->setScale(2.5f);

	_playAgain = new TextSprite("PLAY AGAIN", GVector2(200, 220));
	_playAgain->init();
	_playAgain->setScale(1.75f);

	_endGame = new TextSprite("END GAME", GVector2(200, 270));
	_endGame->init();
	_endGame->setScale(1.75f);

	_flash = new StopWatch();
	_startGame = new StopWatch();

	_choice = true;
	_isPressed = false;
	_isDrawText = false;

	return true;
}

void GameOverScene::updateInput(float deltatime)
{
}

void GameOverScene::onKeyPressed(KeyEventArg* keyEvent)
{
	if (keyEvent->keyCode == DIK_UP || keyEvent->keyCode == DIK_DOWN)
	{
		_choice = !_choice;
	}
	if (keyEvent->keyCode == DIK_Z)
	{
		_isPressed = true;
	}
}

void GameOverScene::update(float dt)
{
	if (_choice)
		_choiceIcon->setPosition(160, 220);
	else
		_choiceIcon->setPosition(160, 270);

	if (_isPressed)
	{
		if (_flash->isTimeLoop(120))
		{
			_isDrawText = !_isDrawText;
		}
		if (_startGame->isStopWatch(600))
		{
			if (_choice)
				SceneManager::getInstance()->replaceScene(new PlayScene());
			else
				SceneManager::getInstance()->replaceScene(new IntroScene());
		}
	}
}

void GameOverScene::draw(LPD3DXSPRITE spriteHandle)
{
	_gameOver->draw(spriteHandle);
	_playAgain->draw(spriteHandle);
	_endGame->draw(spriteHandle);

	if (!_isDrawText)
	{
		_choiceIcon->render(spriteHandle);
	}
}

void GameOverScene::release()
{
	SAFE_DELETE(_gameOver);
	SAFE_DELETE(_playAgain);
	SAFE_DELETE(_endGame);
	SAFE_DELETE(_flash);
	SAFE_DELETE(_startGame);
}
