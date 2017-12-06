#ifndef __GAMEVICTORYSCENE_H__
#define __GAMEVICTORYSCENE_H__

#include "Sprite.h"
#include "SpriteManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "InputController.h"
#include "StopWatch.h"
#include "Animation.h"
#include "TextSprite.h"

[event_receiver(native)]
class VictoryScene : public Scene, public Controlable
{
public:
	VictoryScene();
	~VictoryScene();

	bool init();
	void updateInput(float deltatime);
	void update(float dt);
	void draw(LPD3DXSPRITE spriteHandle);
	void release();

	void onKeyPressed(KeyEventArg* keyEvent);

private:
	Sprite* _sprite;
	vector<Animation*> _samusAnimations;
	int _animationIndex;

	vector<TextSprite*> _text;

	StopWatch* _changeAnimation;
	StopWatch* _startGame;

	bool _isPressed;
};

#endif // !__GAMEVICTORYSCENE_H__
