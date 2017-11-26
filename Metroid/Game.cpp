#include "Game.h"
#include <string>
#include <dinput.h>
#include <d3dx9tex.h>
using namespace std;

bool Game::isExit = false;
Graphics* Game::_hWindow = NULL;

Game::~Game()
{
}

Game::Game(HINSTANCE hInstance, LPWSTR name, int width, int height, int fps, int isFullScreen)
{
	_hWindow = new Graphics(hInstance, name, width, height, fps, isFullScreen);
	_deviceManager = DeviceManager::getInstance();
	_input = InputController::getInstance();
	_spriteHandle = NULL;
	_gameTime = GameTime::getInstance();
}

void Game::init()
{
	if (_hWindow == NULL)
		throw;

	_hWindow->initWindow();
	_gameTime->init();
	_deviceManager->init(*_hWindow);
	_input->init(_hWindow->getWnd(), _hWindow->gethInstance());

	this->_frameTime = 1000.0f / _hWindow->getFrameRate(); // 1000/60 = 16 milisecond

	// Tạo srpite handle
	D3DXCreateSprite(_deviceManager->getDevice(), &this->_spriteHandle);

	this->loadResource();

	_oldTime = _gameTime->getTotalGameTime();
	_deltaTime = 0.0f;
}

void Game::run()
{
	MSG msg;
	while (!isExit)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				isExit = true;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		_gameTime->updateGameTime(); // update thời gian
		_deltaTime = _gameTime->getTotalGameTime() - _oldTime;

		if (_deltaTime >= _frameTime) // _frameRate 1000/60 = 16 milisecond
		{
			_oldTime += _frameTime;
			_input->update();
			this->render();
		}
		else
			Sleep(_frameTime - _deltaTime);
	}
}

void Game::render()
{
	// Kiểm tra nếu cửa sổ không được focus thì không update
	if (GetActiveWindow() != _hWindow->getWnd())
		return;

	auto device = _deviceManager->getInstance();

	// Lấy tổng thời gian trôi qua kể từ lần cuối gọi hàm updateGameTime
	float time = _gameTime->getElapsedGameTime();

	// Xử lý để kéo, resize cửa sổ không bị dồn frame
	if (time > this->_frameTime * 2)
		time = _frameTime;

	// Bắt đầu vẽ
	if (device->getDevice()->BeginScene() != DI_OK)
		return;

	device->clearScreen();

	// Update game
	updateInput(time);
	update(time);
	draw();

	// Kết thúc vẽ
	device->getDevice()->EndScene();

	device->present();
}

void Game::updateInput(float deltatime)
{
}

void Game::update(float deltatime)
{
}

void Game::draw()
{
}

void Game::loadResource()
{
}

void Game::release()
{
	_deviceManager->release();
	_input->release();
	_gameTime->release();
}
