#include "Game.h"
#include <string>
#include <dinput.h>
#include <d3dx9tex.h>
using namespace std;

int Game::isExit = 0;
Graphics* Game::hWindow = NULL;

Graphics* Game::getWindow()
{
	return hWindow;
}

Game::~Game()
{
}

Game::Game(HINSTANCE hInstance, LPWSTR name, int width, int height, int fps, int isFullScreen)
{
	hWindow = new Graphics(hInstance, name, width, height, fps, isFullScreen);
	_deviceManager = DeviceManager::getInstance();
	_input = InputController::getInstance();
	_spriteHandle = NULL;
	_gameTime = GameTime::getInstance();
}

void Game::init()
{
	if (hWindow == NULL)
		throw;

	hWindow->initWindow();
	_gameTime->init();
	_deviceManager->Init(*hWindow);
	_input->init(hWindow->getWnd(), hWindow->gethInstance());

	this->_frameRate = 1000.0f / hWindow->getFrameRate(); // 1000/60 = 16 milisecond

	// Tạo srpite handle
	D3DXCreateSprite(_deviceManager->getDevice(), &this->_spriteHandle);

	this->loadResource();

	_oldTime = _gameTime->getTotalGameTime();
	_deltaTime = 0.0f;
}

void Game::run()
{
	MSG msg;
	while (isExit == 0)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				isExit = 1;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		_gameTime->updateGameTime(); // update thời gian
		_deltaTime = _gameTime->getTotalGameTime() - _oldTime;

		if (_deltaTime >= _frameRate) // _frameRate 1000/60 = 16 milisecond
		{
			_oldTime += _frameRate;
			_input->update();
			this->render();
		}
		else
			Sleep(_frameRate - _deltaTime);
	}
}

void Game::render()
{
	// Kiểm tra nếu cửa sổ không được focus thì không update
	if (GetActiveWindow() != hWindow->getWnd())
		return;

	auto device = _deviceManager->getInstance();

	// Lấy tổng thời gian trôi qua kể từ lần cuối gọi hàm updateGameTime
	float time = _gameTime->getElapsedGameTime();

	// Xử lý kéo cửa sổ không bị dồn frame
	if (time > this->_frameRate * 2)
		time = _frameRate;

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
	_gameTime->release();
	_input->release();
}
