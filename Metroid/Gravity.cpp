#include "Gravity.h"

Gravity::Gravity(GVector2 gravity, Movement* movement)
{
	this->_gravity = gravity;
	this->_refMovement = movement;
	this->_status = FALLING_DOWN;
}

void Gravity::update(float deltatime)
{
	switch (_status)
	{
	case FALLING_DOWN:
		this->_additionalVelocity = this->_gravity * deltatime / 1000;
		break;
	case SHALLOWED:
		this->_additionalVelocity = VECTOR2ZERO;
	default:
		break;
	}

	auto velocity = this->_refMovement->getVelocity();
	this->_refMovement->setVelocity(velocity + _additionalVelocity);
}

eGravityStatus Gravity::getStatus()
{
	return _status;
}

void Gravity::setStatus(eGravityStatus status)
{
	this->_status = status;
}

void Gravity::setGravity(GVector2 gravity)
{
	this->_gravity = gravity;
}
