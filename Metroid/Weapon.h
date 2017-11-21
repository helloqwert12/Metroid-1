#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "define.h"
#include "BaseObject.h"
#include "CollisionBody.h"

class Weapon : public BaseObject
{
public:
	Weapon(eID);
	virtual CollisionBody* getCollisionBody();
};

#endif // !__WEAPON_H__
