#include "Event.h"

EventArg::EventArg() 
{
}

EventArg::~EventArg() 
{
}


KeyEventArg::KeyEventArg(int keyCode)
{
	this->keyCode = keyCode;
}
