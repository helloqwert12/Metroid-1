#include "IComponent.h"

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

void Movement::setAccelerate(GVector2 accelerate)
{
	this->_accelerate = accelerate;
}

void Movement::setVelocity(GVector2 velocicty)
{
	this->_velocity = velocicty;
}

GVector2 Movement::getAccelerate()
{
	return this->_accelerate;
}

GVector2 Movement::getVelocity()
{
	return this->_velocity;
}


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

void Gravity::setStatus(eGravityStatus status)
{
	this->_status = status;
}

eGravityStatus Gravity::getStatus()
{
	return _status;
}

void Gravity::setGravity(GVector2 gravity)
{
	this->_gravity = gravity;
}


SinMovement::SinMovement(GVector2 amplitude, float frequency, Sprite* refsprite)
{
	this->_amplitude = amplitude;
	this->_radian = 0.0f;
	this->_radianVelocity =  2 * M_PI * frequency;
	this->_linearVelocity = _amplitude * _radianVelocity * cos(_radian); // (A * ω * cos(φ))
	this->_refSprite = refsprite;
}

void SinMovement::update(float deltatime)
{
	// góc xoay φ = ω * t
	this->_radian += _radianVelocity * deltatime / 1000;

	// vận tốc tuyến tính v = A * ω * cos(ωt) (lấy đạo hàm)
	this->_linearVelocity = _amplitude * _radianVelocity * cos(_radian);

	auto position = this->_refSprite->getPosition();
	position += _linearVelocity * deltatime / 1000;
	this->_refSprite->setPosition(position);
}

void SinMovement::setAmplitude(GVector2 amplitude)
{
	this->_amplitude = amplitude;
	this->_linearVelocity = _amplitude * _radianVelocity * cos(_radian);
}

void SinMovement::setFrequency(float frequency)
{
	this->_radianVelocity = 2 * M_PI * frequency;
	this->_linearVelocity = _amplitude * _radianVelocity * cos(_radian);
}
