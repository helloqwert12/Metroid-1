#ifndef __VICTORYSCENE_H__
#define __VICTORYSCENE_H__

#include "SpriteManager.h"
#include "SceneManager.h"
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

#endif // !__VICTORYSCENE_H__
