#include <Windows.h>
#include <iostream>
#include "MetroidGame.h"

using namespace std;

#define APP_TITTLE L"Metroid"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpcmdLine, int nCmdShow)
{
	Game* game = new MetroidGame(hInstance, APP_TITTLE);

	game->init();
	game->run();
	game->release();

	delete game;
}
