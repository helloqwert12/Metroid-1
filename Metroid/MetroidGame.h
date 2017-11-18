#ifndef __METROIDGAME_H__
#define __METROIDGAME_H__

#include "Game.h"
#include "define.h"
#include "SpriteManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "IntroScene.h"

class MetroidGame : public Game
{
public:
	MetroidGame(HINSTANCE hInstance, LPWSTR name);
	~MetroidGame();

	void init();
	void release();

	void updateInput(float deltatime);
	void update(float deltatime);
	void draw();
	void loadResource();
};

#endif // !__METROIDGAME_H__
