#include "Movement.h"

Movement::Movement(GVector2 accelerate, GVector2 velocicty, Sprite* refSprite)
{
	this->_accelerate = accelerate;
	this->_velocity = velocicty;
	this->_refSprite = refSprite;
}

void Movement::update(float deltatime)
{
	if (_refSprite == NULL)
		return;

	auto position = this->_refSprite->getPosition();

	this->_velocity += this->_accelerate * deltatime / 1000;
	position += this->_velocity * deltatime / 1000;
	this->_refSprite->setPosition(position);
}

GVector2 Movement::getAccelerate()
{
	return this->_accelerate;
}

void Movement::setAccelerate(GVector2 accelerate)
{
	this->_accelerate = accelerate;
}

GVector2 Movement::getVelocity()
{
	return this->_velocity;
}

void Movement::setVelocity(GVector2 velocicty)
{
	this->_velocity = velocicty;
}
