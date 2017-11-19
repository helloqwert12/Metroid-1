#ifndef __STOPWATCH_H__
#define __STOPWATCH_H__

#include "GameTime.h"

typedef void(*pFunction)();

class StopWatch
{
public:
	StopWatch();
	~StopWatch();

	// Đơn vị milisecond
	bool isTimeLoop(float time);
	bool isStopWatch(float time);
	void timeLoopAction(float time, pFunction action);
	void restart();

private:
	float _stopWatch;
	bool _isStart;
	bool _isFinish;
};

#endif // !__STOPWATCH_H__
