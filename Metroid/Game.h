#ifndef __GAME_H__
#define __GAME_H__

#include <windows.h>
#include "Graphics.h"
#include "DeviceManager.h"
#include "InputController.h"
#include "GameTime.h"

class Game
{
public:
	virtual ~Game();

	static int isExit;

	Game(HINSTANCE, LPWSTR = L"Game", int width = 800, int height = 600, int fps = 60, int isFullScreen = 0);

	void virtual init();
	void virtual release();

	void virtual updateInput(float deltatime);
	void virtual update(float deltatime);
	void virtual draw();
	void virtual loadResource();

	void run();
	void render();
	static void exit();
	static Graphics* getWindow();

protected:
	static Graphics *hWindow;
	DeviceManager* _deviceManager;
	InputController* _input;
	LPD3DXSPRITE _spriteHandle;
	GameTime* _gameTime;

private:
	float _frameRate;	// Thời gian của 1 frame (milisecond)
	float _oldTime;
	float _deltaTime;
};

#endif // !__GAME_H__
