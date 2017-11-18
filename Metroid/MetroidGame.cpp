#include "MetroidGame.h"

MetroidGame::MetroidGame(HINSTANCE hInstance, LPWSTR name) : Game(hInstance, name, WINDOW_WIDTH, WINDOW_HEIGHT)
{
}

MetroidGame::~MetroidGame()
{
}

void MetroidGame::init()
{
	Game::init();

	SceneManager::getInstance()->addScene(new IntroScene());
}

void MetroidGame::release()
{
	Game::release();

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
	// Game::init() đã gọi hàm loadResource này rồi nên không cần gọi lại MetroidGame::loadResource()
	SpriteManager::getInstance()->loadResource(_spriteHandle);
	SoundManager::getInstance()->loadSound(Game::hWindow->getWnd());
}
