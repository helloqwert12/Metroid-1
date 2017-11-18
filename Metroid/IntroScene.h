#ifndef __INTROSCENE_H__
#define __INTROSCENE_H__

#include "Sprite.h"
#include "SpriteManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "InputController.h"
#include "StopWatch.h"
#include "IComponent.h"
#include "BaseObject.h"
#include "TextSprite.h"

[event_receiver(native)]
class IntroScene : public Scene, public IControlable
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
