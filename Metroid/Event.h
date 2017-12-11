#ifndef __EVENT_H__
#define __EVENT_H__

class EventArg
{
public:
	EventArg();
	~EventArg();
};


class KeyEventArg : public EventArg
{
public:
	int keyCode;

	KeyEventArg(int keyCode);
};

#endif // !__EVENT_H__
