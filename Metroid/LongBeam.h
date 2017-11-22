#ifndef __LONGBEAM_H__
#define __LONGBEAM_H__

#include "define.h"
#include "BaseObject.h"
#include "IComponent.h"
#include "CollisionBody.h"
#include "Animation.h"
#include "StopWatch.h"

class LongBeam : public BaseObject
{
public:
	LongBeam(int x, int y);

	void init();
	void update(float deltatime);
	void draw(LPD3DXSPRITE, Viewport*);
	void release();

	float checkCollision(BaseObject* object, float dt);

protected:
	Animation* _animation;
	map<string, IComponent*> _componentList;
};

#endif // !__LONGBEAM_H__
