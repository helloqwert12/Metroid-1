﻿#include "Player.h"
#include "SceneManager.h"

Player::Player(int life) : BaseObject(eID::PLAYER)
{
	_lifeNum = life;
}

Player::~Player()
{
}

void Player::init()
{
	__hook(&InputController::__eventkeyPressed, _input, &Player::onKeyPressed);
	__hook(&InputController::__eventkeyReleased, _input, &Player::onKeyReleased);

	_sprite = SpriteManager::getInstance()->getSprite(eID::PLAYER);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::PLAYER, "default_01"));
	_sprite->setZIndex(1.0f);

	auto movement = new Movement(GVector2(0, 0), GVector2(0, 0), _sprite);

	_componentList["Movement"] = movement;
	_componentList["Gravity"] = new Gravity(GVector2(0, -GRAVITY), movement);

	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;

	_animations[eStatus::NORMAL] = new Animation(_sprite, 0.1f);
	_animations[eStatus::NORMAL]->addFrameRect(eID::PLAYER, "default_01", NULL);

	_animations[eStatus::RUNNING] = new Animation(_sprite, 0.1f);
	_animations[eStatus::RUNNING]->addFrameRect(eID::PLAYER, "walk_right_01", "walk_right_02", "walk_right_03", NULL);

	_animations[eStatus::JUMPING] = new Animation(_sprite, 0.1f);
	_animations[eStatus::JUMPING]->addFrameRect(eID::PLAYER, "jump_01", NULL);

	_animations[eStatus::FALLING] = new Animation(_sprite, 0.1f);
	_animations[eStatus::FALLING]->addFrameRect(eID::PLAYER, "default_01", NULL);

	_animations[eStatus::STAND_UP] = new Animation(_sprite, 0.1f);
	_animations[eStatus::STAND_UP]->addFrameRect(eID::PLAYER, "default_01", NULL);

	_animations[eStatus::STAND_DOWN] = new Animation(_sprite, 0.1f);
	_animations[eStatus::STAND_DOWN]->addFrameRect(eID::PLAYER, "default_01", NULL);

	this->setOrigin(GVector2(0.5f, 0.0f));
	this->setStatus(eStatus::NORMAL);

	// Create stopWatch
	_stopWatch = new StopWatch();

	this->resetValues();

	_info = new Info(GVector2(50, 50), this->getLifeNumber());
	_info->init();
}

void Player::update(float deltatime)
{
	this->checkPosition();

	this->updateStatus(deltatime);

	this->updateCurrentAnimateIndex();

	_animations[_currentAnimateIndex]->update(deltatime);

	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		it->second->update(deltatime);
	}
}

void Player::updateInput(float dt)
{
	// Use event instead
}

void Player::updateStatus(float dt)
{
	if (this->isInStatus(eStatus::DIE))
	{
		if (_lifeNum < 0)
		{
			return;
		}
		if (!_animations[eStatus::DIE]->isAnimate())
		{
			this->revive();
		}
		return;
	}

	if ((this->getStatus() & eStatus::MOVING_LEFT) == eStatus::MOVING_LEFT)
	{
		this->moveLeft();
	}
	else if ((this->getStatus() & eStatus::MOVING_RIGHT) == eStatus::MOVING_RIGHT)
	{
		this->moveRight();
	}
	else if ((this->getStatus() & eStatus::FALLING) == eStatus::FALLING)
	{
		this->falling();
	}
	else if ((this->getStatus() & eStatus::JUMPING) != eStatus::JUMPING)
	{
		this->standing();
	}
}

void Player::updateCurrentAnimateIndex()
{
	_currentAnimateIndex = this->getStatus();

	if ((_currentAnimateIndex & eStatus::FALLING) == eStatus::FALLING)
	{
		_currentAnimateIndex = eStatus::FALLING;
	}

	if ((_currentAnimateIndex & eStatus::MOVING_LEFT) == eStatus::MOVING_LEFT || ((_currentAnimateIndex & eStatus::MOVING_RIGHT) == eStatus::MOVING_RIGHT))
	{
		_currentAnimateIndex = (eStatus)(_currentAnimateIndex & ~(eStatus::MOVING_LEFT | MOVING_RIGHT));
		
		_currentAnimateIndex = (eStatus)(_currentAnimateIndex | eStatus::RUNNING);
	}

	if ((_currentAnimateIndex & eStatus::JUMPING) == eStatus::JUMPING)
	{
		_currentAnimateIndex = eStatus::JUMPING;
	}

	if (this->isInStatus(eStatus::DIE))
	{
		_currentAnimateIndex = eStatus::DIE;
	}
}

void Player::resetValues()
{
	this->setScale(SCALE_FACTOR);

	_movingSpeed = MOVE_SPEED;

	for (auto animate : _animations)
	{
		animate.second->setColorFlash(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

void Player::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	_animations[_currentAnimateIndex]->draw(spriteHandle, viewport);
	_info->draw(spriteHandle, viewport);
}

void Player::release()
{
	for (auto it = _animations.begin(); it != _animations.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_animations.clear();

	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();

	SAFE_DELETE(_sprite);
	SAFE_DELETE(_stopWatch);
	SAFE_DELETE(_info);

	if (_input != nullptr)
		__unhook(_input);
}

void Player::onKeyPressed(KeyEventArg* key_event)
{
	if (this->isInStatus(eStatus::DIE))
		return;

	switch (key_event->_key)
	{
	case DIK_LEFT:
	{
		if (!this->isInStatus(eStatus::JUMPING))
		{
			this->removeStatus(eStatus::MOVING_RIGHT);
			this->addStatus(eStatus::MOVING_LEFT);
		}
		break;
	}
	case DIK_RIGHT:
	{
		if (!this->isInStatus(eStatus::JUMPING))
		{
			this->removeStatus(eStatus::MOVING_LEFT);
			this->addStatus(eStatus::MOVING_RIGHT);
		}
		break;
	}
	case DIK_UP:
	{
		break;
	}
	case DIK_DOWN:
	{
		break;
	}
	case DIK_X:
	{
		if (!this->isInStatus(eStatus::SIT_DOWN) || this->isInStatus(eStatus::MOVING_LEFT) || this->isInStatus(eStatus::MOVING_RIGHT))
			this->jump();
		break;
	}
	case DIK_Z:
	{
		break;
	}
	default:
		break;
	}
}

void Player::onKeyReleased(KeyEventArg* key_event)
{
	if (this->isInStatus(eStatus::DIE))
		return;

	switch (key_event->_key)
	{
	case DIK_LEFT:
	{
		this->removeStatus(eStatus::MOVING_LEFT);
		break;
	}
	case DIK_RIGHT:
	{
		this->removeStatus(eStatus::MOVING_RIGHT);
		break;
	}
	case DIK_UP:
	{
		break;
	}
	case DIK_DOWN:
	{
		break;
	}
	case DIK_X:
	{
		break;
	}
	case DIK_Z:
	{
		break;
	}
	default:
		break;
	}
}

//void Player::onCollisionBegin(CollisionEventArg* collision_arg)
//{
//}
//
//void Player::onCollisionEnd(CollisionEventArg* collision_event)
//{
//	eID objectID = collision_event->_otherObject->getId();
//
//	switch (objectID)
//	{
//	case eID::WALL:
//	{
//		if (preWall == collision_event->_otherObject)
//		{
//			// hết chạm với land là fall chứ không có jump
//			this->removeStatus(eStatus::JUMPING);
//			preWall = nullptr;
//		}
//		break;
//	}
//
//	default:
//		break;
//	}
//}

float Player::checkCollision(BaseObject* object, float dt)
{
	if (object->getStatus() == eStatus::DESTROY || this->isInStatus(eStatus::DIE))
		return 0.0f;

	if (this == object)
		return 0.0f;

	auto collisionBody = (CollisionBody*)_componentList["CollisionBody"];
	eID objectId = object->getId();
	eDirection direction;

	if (objectId == eID::WALL)
	{
		if (collisionBody->checkCollision(object, direction, dt, false))
		{
			float moveX, moveY;
			if (collisionBody->isColliding(object, moveX, moveY, dt))
			{
				collisionBody->updateTargetPosition(object, direction, false, GVector2(moveX, moveY));
			}

			if (direction == eDirection::TOP && !(this->getVelocity().y > -200 && this->isInStatus(eStatus::JUMPING)))
			{
				auto gravity = (Gravity*)this->_componentList["Gravity"];
				gravity->setStatus(eGravityStatus::SHALLOWED);

				this->standing();
				preWall = object;
			}
		}
		else if (preWall == object)
		{
			auto gravity = (Gravity*)this->_componentList["Gravity"];


			if (!this->isInStatus(eStatus::MOVING_DOWN)
				&& !this->isInStatus(eStatus::MOVING_UP)
				&& !this->isInStatus(eStatus::STAND_DOWN)
				&& !this->isInStatus(eStatus::STAND_UP))
			{
				gravity->setStatus(eGravityStatus::FALLING__DOWN);
				if (!this->isInStatus(eStatus::JUMPING) && !this->isInStatus(eStatus::FALLING))
					this->addStatus(eStatus::FALLING);
			}
		}
	}
}

void Player::checkPosition()
{
	if (this->isInStatus(eStatus::DIE))
		return;

	auto viewport = SceneManager::getInstance()->getCurrentScene()->getViewport();
	GVector2 viewport_position = viewport->getPositionWorld();

	if (this->getPositionY() < viewport_position.y - WINDOW_HEIGHT)
	{
		if (_status != eStatus::DIE)
			_status = eStatus::DIE;
		this->die();
	}
}

void Player::standing()
{
	auto move = (Movement*)this->_componentList["Movement"];
	move->setVelocity(GVector2(0, 0));

	this->removeStatus(eStatus::JUMPING);
	this->removeStatus(eStatus::FALLING);
}

void Player::moveLeft()
{
	if (this->getScale().x > 0)
		this->setScaleX(this->getScale().x * (-1));

	auto move = (Movement*)this->_componentList["Movement"];
	move->setVelocity(GVector2(-_movingSpeed, move->getVelocity().y));
}

void Player::moveRight()
{
	if (this->getScale().x < 0)
		this->setScaleX(this->getScale().x * (-1));

	auto move = (Movement*)this->_componentList["Movement"];
	move->setVelocity(GVector2(_movingSpeed, move->getVelocity().y));
}

void Player::jump()
{
	if (this->isInStatus(eStatus::JUMPING) || this->isInStatus(eStatus::FALLING))
		return;

	this->addStatus(eStatus::JUMPING);

	auto move = (Movement*)this->_componentList["Movement"];
	move->setVelocity(GVector2(move->getVelocity().x, JUMP_VELOCITY));

	auto g = (Gravity*)this->_componentList["Gravity"];
	g->setStatus(eGravityStatus::FALLING__DOWN);
}

void Player::falling()
{
	auto gravity = (Gravity*)this->_componentList["Gravity"];
	gravity->setStatus(eGravityStatus::FALLING__DOWN);
}

void Player::die()
{
	if (!this->isInStatus(eStatus::DIE))
		this->setStatus(eStatus::DIE);

	auto move = (Movement*)this->_componentList["Movement"];
	move->setVelocity(GVector2(-MOVE_SPEED * (this->getScale().x / SCALE_FACTOR), JUMP_VELOCITY));

	auto g = (Gravity*)this->_componentList["Gravity"];
	g->setStatus(eGravityStatus::FALLING__DOWN);
}

void Player::revive()
{
}

void Player::setLifeNumber(int number)
{
	_lifeNum = number;
}

int Player::getLifeNumber()
{
	return _lifeNum;
}

void Player::setStatus(eStatus status)
{
	_status = status;
}

RECT Player::getBounding()
{
	RECT bound = _sprite->getBounding();
	return bound;
}

GVector2 Player::getVelocity()
{
	auto move = (Movement*)this->_componentList["Movement"];
	return move->getVelocity();
}
