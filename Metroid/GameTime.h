#ifndef __GAMETIME_H__
#define __GAMETIME_H__

#include "define.h"
#include "TimeSpan.h"

class GameTime
{
public:
	~GameTime();

	static void release();
	static GameTime* getInstance();
	void init();
	void resetLastTick();
	void updateGameTime();

	float getTotalGameTime();	// Tổng thời gian trôi qua kể từ lúc gọi hàm init()
	float getElapsedGameTime(); // Tổng thời gian trôi qua kể từ lần cuối gọi hàm updateGameTime()

private:
	static GameTime* _instance;

	TimeSpan _totalGameTime;
	TimeSpan _elapsedGameTime;
	LARGE_INTEGER _query;
	float _freQuery; // Số giây trong 1 tick

	LONGLONG startTicks;
	LONGLONG lastTicks;
	LONGLONG currentTicks;

	GameTime(TimeSpan& elapsedGameTime);
	GameTime();

	void setTotalGameTime(TimeSpan& totalGametime);
	void setElapsedGameTime(TimeSpan& elapsedGametime);
};

#endif // !__GAMETIME_H__
