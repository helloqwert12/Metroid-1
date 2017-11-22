#ifndef __ICE_BEAM_H__
#define __ICE_BEAM_H__

#include "define.h"
#include "BaseObject.h"
#include "IComponent.h"
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
	map<string, IComponent*> _componentList;
};

#endif // !__ICE_BEAM_H__
