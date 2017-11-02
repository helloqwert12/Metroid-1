#ifndef __METROID_GAME_H__
#define __METROID_GAME_H__

#include "Game.h"
#include "define.h"
#include "SpriteManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "IntroScene.h"

class MetroidGame : public Game
{
public:
	MetroidGame(HINSTANCE hInstance, LPWSTR title);
	~MetroidGame();

	void init();						// init your objects
	void release();						// release your objects

	void updateInput(float deltatime);	// update input, include played objects and menu button
	void update(float deltatime);		// update your objects
	void draw();						// draw your objects
	void loadResource();

private:

};

#endif // !__METROID_GAME_H__
