#include "MetroidGame.h"

MetroidGame::MetroidGame(HINSTANCE hInstance, LPWSTR title) : Game(hInstance, title, WINDOW_WIDTH, WINDOW_HEIGHT)
{
}

MetroidGame::~MetroidGame()
{
}

void MetroidGame::init()
{
	Game::init();
	// init game
#if _DEBUG
	SceneManager::getInstance()->addScene(new IntroScene());
#else
	SceneManager::getInstance()->addScene(new IntroScene());
#endif
}

void MetroidGame::release()
{
	Game::release();

	// release game
	SceneManager::getInstance()->clearScenes();
}

void MetroidGame::updateInput(float deltatime)
{
	SceneManager::getInstance()->updateInput(deltatime);
}

void MetroidGame::update(float deltatime)
{
	SceneManager::getInstance()->update(deltatime);
}

void MetroidGame::draw()
{
	this->_spriteHandle->Begin(D3DXSPRITE_ALPHABLEND);

	SceneManager::getInstance()->draw(_spriteHandle);

	this->_spriteHandle->End();
}

void MetroidGame::loadResource()
{
	// Game::init đã gọi hàm này rồi nên không cần gọi lại MetroidGame::loadResource
	// load resource
	SpriteManager::getInstance()->loadResource(_spriteHandle);
	SoundManager::getInstance()->loadSound(Game::hWindow->getWnd());
}
