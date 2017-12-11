#ifndef __INTROSCENE_H__
#define __INTROSCENE_H__

#include "SpriteManager.h"
#include "SceneManager.h"
#include "StopWatch.h"
#include "Component.h"
#include "BaseObject.h"
#include "TextSprite.h"

[event_receiver(native)]
class IntroScene : public Scene, public Controlable
{
public:
	IntroScene();
	~IntroScene();

	bool init();
	void updateInput(float deltatime);
	void update(float dt);
	void draw(LPD3DXSPRITE spriteHandle);
	void release();

	void onKeyPressed(KeyEventArg* keyEvent);

private:
	Sprite* _background;

	TextSprite* _pressStart;
	TextSprite* _lecturer;
	TextSprite* _thienAn;
	TextSprite* _huuDat;
	TextSprite* _siDat;
	TextSprite* _leHuy;

	StopWatch* _flash;
	StopWatch* _startGame;

	bool _isPressed;
	bool _isDrawText;
};

#endif // !__INTROSCENE_H__
