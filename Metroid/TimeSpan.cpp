#include "TimeSpan.h"

TimeSpan::TimeSpan()
{
}

TimeSpan::~TimeSpan()
{
}

TimeSpan::TimeSpan(UINT64 ticks)
{
	this->_ticks = ticks;
}

float TimeSpan::getMiliSeconds()
{
	return ((float)_ticks) / TicksPerMilisecond;
}

UINT64 TimeSpan::getTicks()
{
	return _ticks;
}

TimeSpan TimeSpan::operator+(TimeSpan timeSpan)
{
	return TimeSpan(this->_ticks + timeSpan._ticks);
}

TimeSpan TimeSpan::operator+(UINT64 timeSpan)
{
	return TimeSpan(*this + TimeSpan(timeSpan));
}
