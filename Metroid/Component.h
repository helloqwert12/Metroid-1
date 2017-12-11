#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <map>

class Component
{
public:
	virtual void update(float deltatime) = 0;
};

#endif // !__COMPONENT_H__
