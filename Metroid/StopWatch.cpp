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

// Đơn vị milisecond
bool StopWatch::isTimeLoop(float time)
{
	// Lấy thời gian hiện tại
	float totalGameTime = GameTime::getInstance()->getTotalGameTime();

	// Nếu chưa bắt đầu thì bắt đầu
	if (!_isStart)
	{
		// Tính thời gian kết thúc
		_stopWatch = time + totalGameTime;
		_isStart = true;
		return false;
	}

	float deltaTime = _stopWatch - totalGameTime;

	// Nếu quá thời gian kết thúc thì return TRUE
	// đồng thời tính thời gian kết thúc tiếp theo (do loop)
	if (deltaTime <= 0)
	{
		_stopWatch = time + deltaTime + totalGameTime;
		return true;
	}

	return false;
}

bool StopWatch::isStopWatch(float time)
{
	if (_isFinish)
		return false;

	// Lấy thời gian hiện tại
	float totalGameTime = GameTime::getInstance()->getTotalGameTime();
	if (!_isStart)
	{
		_stopWatch = time + totalGameTime;
		_isStart = true;
		return false;
	}

	float deltaTime = _stopWatch - totalGameTime;

	// Nếu quá thời gian kết thúc thì return TRUE
	// và set _isFinish = TRUE
	if (deltaTime <= 0)
	{
		_isFinish = true;
		return true;
	}

	return false;
}

void StopWatch::timeLoopAction(float time, pFunction action)
{
	if (isTimeLoop(time))
	{
		(*action)();
	}
}

void StopWatch::restart()
{
	_isStart = false;
	_isFinish = false;
}
