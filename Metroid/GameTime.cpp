#include "GameTime.h"

GameTime* GameTime::_instance = nullptr;

GameTime::GameTime()
{
}

GameTime::GameTime(TimeSpan& elapsedGameTime)
{
	this->_elapsedGameTime = elapsedGameTime;
}

GameTime::~GameTime()
{
}

GameTime* GameTime::getInstance()
{
	if (_instance == nullptr)
		_instance = new GameTime();
	return _instance;
}

void GameTime::release()
{
	delete _instance;
	_instance = NULL;
}

void GameTime::init()
{
	// Trả về số lượng tick trong 1 second (TickPerSecond)
	QueryPerformanceFrequency(&this->_Query);

	// Tính số giây trong 1 tick
	this->_freQuery = (float)_Query.QuadPart / TimeSpan::TicksPerSecond;

	// Hàm trả về milisecond
	QueryPerformanceCounter(&_Query);
	startTicks = lastTicks = _Query.QuadPart;
	_totalGameTime = (TimeSpan)0;
}

void GameTime::resetLastTick()
{
	lastTicks = 0;
	curTicks = 0;
	_totalGameTime = (TimeSpan)0;
}

void GameTime::updateGameTime()
{
	QueryPerformanceCounter(&_Query);
	curTicks = _Query.QuadPart;

	if ((UINT64)((float)(curTicks - lastTicks) / _freQuery) < TimeSpan::TicksPerMilisecond * 16) // 1000/60 = 16 milisecond
	{
		return;
	}

	auto gameTime = ((float)(curTicks - lastTicks)) / _freQuery; // đơn vị tick

	this->setTotalGameTime(_totalGameTime + gameTime);
	this->setElapsedGameTime(TimeSpan((UINT64)gameTime));

	lastTicks = curTicks;
}

float GameTime::getTotalGameTime()
{
	return this->_totalGameTime.getMiliSeconds();
}

float GameTime::getElapsedGameTime()
{
	return this->_elapsedGameTime.getMiliSeconds();
}

void GameTime::setTotalGameTime(TimeSpan& totalGametime)
{
	this->_totalGameTime = totalGametime;
}

void GameTime::setElapsedGameTime(TimeSpan& elapsedGametime)
{
	this->_elapsedGameTime = elapsedGametime;
}
