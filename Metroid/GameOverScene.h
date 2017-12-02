#ifndef __GAMEOVERSCENE_H__
#define __GAMEOVERSCENE_H__

#include "Sprite.h"
#include "SpriteManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "InputController.h"
#include "StopWatch.h"
#include "Component.h"
#include "BaseObject.h"
#include "TextSprite.h"

[event_receiver(native)]
class GameOverScene : public Scene, public Controlable
{
public:
	GameOverScene();
	~GameOverScene();

	bool init();
	void updateInput(float deltatime);
	void update(float dt);
	void draw(LPD3DXSPRITE spriteHandle);
	void release();

	void onKeyPressed(KeyEventArg* keyEvent);

private:
	Sprite* _choiceIcon;
	TextSprite* _gameOver;
	TextSprite* _playAgain;
	TextSprite* _endGame;

	StopWatch* _flash;
	StopWatch* _startGame;

	bool _choice;
	bool _isPressed;
	bool _isDrawText;
};

#endif // !__GAMEOVERSCENE_H__
