#ifndef __STOPWATCH_H__
#define __STOPWATCH_H__

#include "GameTime.h"

class StopWatch
{
public:
	StopWatch();
	~StopWatch();

	// Đơn vị milisecond
	bool isStopWatch(float time);
	bool isTimeLoop(float time);
	void restart();

private:
	float _stopWatch;
	bool _isStart;
	bool _isFinish;
};

#endif // !__STOPWATCH_H__
