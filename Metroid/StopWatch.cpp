#include "StopWatch.h"

StopWatch::StopWatch()
{
	_stopWatch = 0.0f;
	_isStart = false;
	_isFinish = false;
}

StopWatch::~StopWatch()
{
}

bool StopWatch::isFinish()
{
	return this->_isFinish;
}

// Đơn vị milisecond
bool StopWatch::isTimeLoop(float time)
{
	float totalGameTime = GameTime::getInstance()->getTotalGameTime();
	if (!_isStart)
	{
		_stopWatch = time + totalGameTime;
		_isStart = true;
		return false;
	}

	float delta = _stopWatch - totalGameTime;
	if (delta <= 0)
	{
		_stopWatch = time + delta + totalGameTime;
		return true;
	}

	return false;
}

bool StopWatch::isStopWatch(float time)
{
	if (_isFinish)
		return false;

	float totalGameTime = GameTime::getInstance()->getTotalGameTime();
	if (!_isStart)
	{
		_stopWatch = time + totalGameTime;
		_isStart = true;
		return false;
	}

	float delta = _stopWatch - totalGameTime;
	if (delta <= 0)
	{
		_isFinish = true;
		return true;
	}

	return false;
}

void StopWatch::restart()
{
	_isStart = false;
	_isFinish = false;
}

void StopWatch::timeLoopAction(float time, pFunction action)
{
	if (isTimeLoop(time))
	{
		(*action)();
	}
}
