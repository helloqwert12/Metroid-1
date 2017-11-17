#include "Waver.h"

Waver::Waver(int x, int y, bool direct) : BaseObject(WAVER)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::ENEMY);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ENEMY, "gr_waver_01"));
	_sprite->setScale(SCALE_FACTOR);
	_sprite->setPosition(x, y);

	_animation = new Animation(_sprite, 0.2f);
	_animation->addFrameRect(eID::ENEMY, "gr_waver_01", "gr_waver_02", "gr_waver_03", NULL);

	//_effect = SpriteManager::getInstance()->getSprite(eID::EFFECT);
	//_effect->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::EFFECT, "hit_effect_1"));
	//_effectAnimation = new Animation(_effect, 0.15f);
	//_effectAnimation->addFrameRect(EFFECT, "hit_effect_1", "hit_effect_2", "hit_effect_3", NULL);

	_hitPoint = 2;
	_isActive = false;

	auto movement = new Movement(GVector2(0, 0), GVector2(0, 0), _sprite);
	_componentList["Movement"] = movement;
}

void Waver::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;

	_effectStopWatch = new StopWatch();
	_hitStopWatch = new StopWatch();
	_startHit = false;
}

void Waver::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	if (_hitPoint > 0)
		_animation->draw(spriteHandle, viewport);
	else
	{
		if (_isActive)
			_animation->draw(spriteHandle, viewport);
		else
			_sprite->render(spriteHandle, viewport);
	}
}

void Waver::update(float deltatime)
{
	if (_hitPoint > 0)
	{
		if (_isActive) {
			_animation->update(deltatime);
			auto move = (Movement*)this->_componentList["Movement"];

			if (_startHit)
			{
				if (_hitStopWatch->isStopWatch(400))
				{
					_startHit = false;
					_hitStopWatch->restart();
				}
			}

			if (_startHit)
			{
				move->setVelocity(GVector2(0, 0));
			}
		}

		for (auto it = _componentList.begin(); it != _componentList.end(); it++)
		{
			it->second->update(deltatime);
		}
	}
	else
	{
		//_effect->setPosition(this->getPosition());
		//_effectAnimation->update(deltatime);

		//if (_effectStopWatch->isStopWatch(600))
		//{
		//	this->setStatus(DESTROY);
		//	srand(time(0));
		//	auto ran = rand() % 10;
		//	BaseObject* item = nullptr;
		//	if (ran < 5)
		//		item = new Enegy(this->getPositionX(), this->getPositionY());
		//	if (item != nullptr)
		//	{
		//		item->init();
		//		QuadTreeNode::getInstance()->insert(item);
		//	}
		//}
	}
}

void Waver::wasHit(int hitpoint)
{
	if (!_startHit)
	{
		_hitPoint -= hitpoint;
		_hitStopWatch->restart();
		_hitStopWatch->isTimeLoop(400);
		_startHit = true;
	}

	if (_hitPoint <= 0)
	{
		auto move = (Movement*)this->_componentList["Movement"];
		move->setVelocity(GVector2(0, 0));
		_effectStopWatch->isTimeLoop(600);
	}
}

bool Waver::isDead()
{
	return (_hitPoint <= 0);
}

void Waver::active(bool direct)
{
	_isActive = true;

	auto sinmovement = new SinMovement(GVector2(0, 150), 0.5, _sprite);
	this->_componentList["SinMovement"] = sinmovement;

	auto movement = (Movement*)this->_componentList["Movement"];
	if (direct)
	{
		_sprite->setScaleX(_sprite->getScale().x * -1);
		movement->setVelocity(GVector2(WAVER_MOVE_SPEED, 0));
	}
	else
	{
		movement->setVelocity(GVector2(-WAVER_MOVE_SPEED, 0));
	}
}

void Waver::deactive()
{
	_isActive = false;

	auto movement = (Movement*)this->_componentList["Movement"];
	movement->setVelocity(GVector2(0, 0));

	auto sinMovement = (Movement*)this->_componentList["SinMovement"];
	_componentList.erase("SinMovement");
	delete sinMovement;
}

bool Waver::isActive()
{
	return _isActive;
}

float Waver::checkCollision(BaseObject* object, float dt)
{
	if (object->getId() == WALL)
	{
		auto collisionBody = (CollisionBody*)_componentList["CollisionBody"];
		eDirection direction;
		if (collisionBody->checkCollision(object, direction, dt, false))
		{
			if (direction == LEFT || direction == RIGHT)
			{
				float moveX, moveY;
				if (collisionBody->isColliding(object, moveX, moveY, dt))
				{
					collisionBody->updateTargetPosition(object, direction, false, GVector2(moveX, moveY));

					// Va chạm Wall LEFT hoặc RIGHT thì đi ngược lại
					auto movement = (Movement*)this->_componentList["Movement"];
					movement->setVelocity(GVector2(-movement->getVelocity().x, 0));
					this->setScale(this->getScale() * -1);
				}
			}
			else if (direction == TOP || direction == BOTTOM)
			{
				float moveX, moveY;
				if (collisionBody->isColliding(object, moveX, moveY, dt))
				{
					// Va chạm Wall TOP hoặc BOTTOM thì update lại vị trí (tránh không cho đi xuyên)
					collisionBody->updateTargetPosition(object, direction, false, GVector2(moveX, moveY));
				}
			}
			return 1.0f;
		}
	}
	return 0;
}

void Waver::release()
{
	SAFE_DELETE(_animation);
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}
