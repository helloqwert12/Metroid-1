#ifndef __ICEBEAM_H__
#define __ICEBEAM_H__

#include "define.h"
#include "BaseObject.h"
#include "Component.h"
#include "CollisionBody.h"
#include "Animation.h"
#include "StopWatch.h"

class IceBeam : public BaseObject
{
public:
	IceBeam(int x, int y);

	void init();
	void update(float deltatime);
	void draw(LPD3DXSPRITE, Viewport*);
	void release();

	float checkCollision(BaseObject* object, float dt);

protected:
	Animation* _animation;
	map<string, Component*> _componentList;
};

#endif // !__ICEBEAM_H__
