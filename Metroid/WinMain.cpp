#include <Windows.h>
#include <iostream>
#include "MetroidGame.h"
using namespace std;

#define GAME_NAME L"Metroid"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpcmdLine, int nCmdShow)
{
	Game* game = new MetroidGame(hInstance, GAME_NAME);

	game->init();
	game->run();
	game->release();

	delete game;
}
