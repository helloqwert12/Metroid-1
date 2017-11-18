#ifndef __TIMESPAN_H__
#define	__TIMESPAN_H__

#include "define.h"

class TimeSpan
{
public:
	static const UINT64 TicksPerSecond = 10000000;	// Số tick trong 1 second
	static const UINT64 TicksPerMilisecond = 10000;	// Số tick trong 1 milisecond
	// 1 tick = 100 nanosecond

	TimeSpan();
	TimeSpan(UINT64);
	~TimeSpan();

	float getMiliSeconds();	// Lấy thời gian (milisecond)
	UINT64 getTicks();

	TimeSpan operator +(TimeSpan);
	TimeSpan operator +(UINT64);

private:
	UINT64 _ticks;
};

#endif // !__TIMESPAN_H__
