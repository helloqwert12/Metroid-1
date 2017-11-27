#include "SinMovement.h"

SinMovement::SinMovement(GVector2 amplitude, float frequency, Sprite* refsprite)
{
	this->_amplitude = amplitude;
	this->_radian = 0.0f;
	this->_radianVelocity = 2 * M_PI * frequency;
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
