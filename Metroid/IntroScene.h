#ifndef __INTRO_SCENE__
#define __INTRO_SCENE__

#include "Sprite.h"
#include "SpriteManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "InputController.h"
#include "StopWatch.h"
#include "IComponent.h"
#include "BaseObject.h"
#include "TextSprite.h"

EVENT_RECEIVER
class IntroScene : public Scene, public IControlable
{
public:
	IntroScene();
	~IntroScene();

	bool init() override;
	void update(float dt) override;
	void draw(LPD3DXSPRITE spriteHandle) override;
	void release() override;
	void updateInput(float deltatime) override;

private:
	Sprite* _introtable;

	void onKeyPressed(KeyEventArg* key_event);

	StopWatch* _flash;
	StopWatch* _access;
	bool _ok;
	bool _draw;

	TextSprite* _gameTitle;
	TextSprite* _playOption;
	TextSprite* _thienAn;
	TextSprite* _huuDat;
	TextSprite* _siDat;
	TextSprite* _leHuy;
};

#endif // !__INTRO_SCENE__
