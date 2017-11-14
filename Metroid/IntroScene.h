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

[event_receiver(native)]
class IntroScene : public Scene, public IControlable
{
public:
	IntroScene();
	~IntroScene();

	bool init() override;
	void updateInput(float deltatime) override;
	void update(float dt) override;
	void draw(LPD3DXSPRITE spriteHandle) override;
	void release() override;

	void onKeyPressed(KeyEventArg* keyEvent);

private:
	Sprite* _background;

	TextSprite* _playOption;
	TextSprite* _thienAn;
	TextSprite* _huuDat;
	TextSprite* _siDat;
	TextSprite* _leHuy;

	StopWatch* _flash;
	StopWatch* _access;

	bool _ok;
	bool _draw;
};

#endif // !__INTRO_SCENE__
