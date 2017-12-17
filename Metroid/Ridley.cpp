#include "Ridley.h"
#include "SceneManager.h"
#include "PlayScene.h"
#include "SoundManager.h"

Ridley::Ridley(int x, int y) : BaseObject(RIDLEY)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::RIDLEY);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::RIDLEY, "ridley_normal_01"));
	_sprite->setPosition(x, y);

	_animations[eStatus::NORMAL] = new Animation(_sprite, 0.07f);
	_animations[eStatus::NORMAL]->addFrameRect(eID::RIDLEY, "ridley_normal_01", "ridley_normal_02", NULL);

	_animations[eStatus::JUMPING] = new Animation(_sprite, 0.07f);
	_animations[eStatus::JUMPING]->addFrameRect(eID::RIDLEY, "flying_ridley_01", "flying_ridley_02", NULL);

	_currentAnimationIndex = eStatus::NORMAL;

	_effect = SpriteManager::getInstance()->getSprite(eID::BULLET_EFFECT);
	_effect->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BULLET_EFFECT, "explosion_01"));
	_effectAnimation = new Animation(_effect, 0.1);
	_effectAnimation->addFrameRect(BULLET_EFFECT, "explosion_01", "explosion_02", "explosion_03", NULL);

	_hitPoint = 30;
	_isActive = true;

	auto movement = new Movement(GVector2(0, 0), GVector2(0, 0), _sprite);
	_componentList["Movement"] = movement;
	_componentList["Gravity"] = new Gravity(GVector2(0, -GRAVITY), movement);
}

void Ridley::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;

	_effectStopWatch = new StopWatch();
	_hitStopWatch = new StopWatch();
	_startHitStopWatch = false;

	_ridleyBulletAppearStopWatch = new StopWatch();
	_ridleyJumpStopWatch = new StopWatch();
}

void Ridley::update(float deltatime)
{
	if (_hitPoint > 0)
	{
		// Lấy vị trí của Player
		auto playScene = (PlayScene*)SceneManager::getInstance()->getCurrentScene();
		auto playerPosition = playScene->getPlayer()->getPosition();
		auto ridleyPosition = this->getPosition();

		if (playerPosition.x > ridleyPosition.x + 20)
		{
			if (_sprite->getScale().x < 0)
				_sprite->setScaleX(_sprite->getScale().x * (-1));
		}
		else if (playerPosition.x < ridleyPosition.x - 20)
		{
			if (_sprite->getScale().x > 0)
				_sprite->setScaleX(_sprite->getScale().x * (-1));
		}

		_currentAnimationIndex = this->getStatus();
		_animations[_currentAnimationIndex]->update(deltatime);

		if (_startHitStopWatch)
		{
			// Nếu đang trong thời gian protect thì deactive
			this->deactive();

			// Check để sau khi hết khoảng thời gian protect thì tắt hitStopWatch
			// Active lại
			if (_hitStopWatch->isStopWatch(400))
			{
				_startHitStopWatch = false;
				_hitStopWatch->restart();
				this->active();
			}
		}

		if (_ridleyBulletAppearStopWatch->isStopWatch(RIDLEY_BULLET_APPEAR_TIME))
		{
			RidleyBullet* ridleyBullet = nullptr;
			if (playerPosition.x > ridleyPosition.x + 20)
				ridleyBullet = new RidleyBullet(ridleyPosition.x + 20, ridleyPosition.y + 40, true);
			else
				ridleyBullet = new RidleyBullet(ridleyPosition.x - 20, ridleyPosition.y + 40, false);

			ridleyBullet->init();
			QuadTreeNode::getInstance()->insert(ridleyBullet);

			_ridleyBulletAppearStopWatch->restart();
		}

		if (_ridleyJumpStopWatch->isStopWatch(RIDLEY_JUMP_TIME))
		{
			this->jump();
			_ridleyJumpStopWatch->restart();
		}

		for (auto it = _componentList.begin(); it != _componentList.end(); it++)
		{
			it->second->update(deltatime);
		}
	}
	else
	{
		_effect->setPosition(this->getPosition());
		_effectAnimation->update(deltatime);

		if (_effectStopWatch->isStopWatch(200))
		{
			SoundManager::getInstance()->play(eSoundID::EXPLOSION_SOUND);

			this->setStatus(DESTROY);

			BaseObject* item = nullptr;

			item = new RocketBall(this->getPositionX() - 30, this->getPositionY());
			item->init();
			QuadTreeNode::getInstance()->insert(item);
			
			item = new RocketBall(this->getPositionX(), this->getPositionY());
			item->init();
			QuadTreeNode::getInstance()->insert(item);

			item = new RocketBall(this->getPositionX(), this->getPositionY() + 30);
			item->init();
			QuadTreeNode::getInstance()->insert(item);

			item = new RocketBall(this->getPositionX() + 30, this->getPositionY());
			item->init();
			QuadTreeNode::getInstance()->insert(item);
		}
	}
}

void Ridley::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	if (_hitPoint > 0)
		_animations[_currentAnimationIndex]->draw(spriteHandle, viewport);
	else
		_effectAnimation->draw(spriteHandle, viewport);
}

void Ridley::release()
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
}

void Ridley::wasHit(int hitPoint)
{
	// Nếu không trong khoảng thời gian protect thì trừ HP và bật hitStopWatch
	// Nếu đang trong khoảng thời gian protect thì không trừ HP
	if (!_startHitStopWatch)
	{
		_hitPoint -= hitPoint;
		_hitStopWatch->restart();
		_startHitStopWatch = true;
	}

	if (_hitPoint <= 0)
	{
		auto move = (Movement*)this->_componentList["Movement"];
		move->setVelocity(GVector2(0, 0));
	}
}

bool Ridley::isDead()
{
	return (_hitPoint <= 0);
}

void Ridley::active()
{
	_isActive = true;
}

void Ridley::deactive()
{
	_isActive = false;
}

bool Ridley::isActive()
{
	return _isActive;
}

void Ridley::jump()
{
	if (this->isInStatus(eStatus::JUMPING))
		return;

	this->setStatus(eStatus::JUMPING);

	auto movement = (Movement*)this->_componentList["Movement"];
	movement->setVelocity(GVector2(movement->getVelocity().x, RIDLEY_JUMP_VELOCITY));

	this->fall();
}

void Ridley::fall()
{
	auto gravity = (Gravity*)this->_componentList["Gravity"];
	gravity->setStatus(eGravityStatus::FALLING_DOWN);
}

void Ridley::stand()
{
	auto movement = (Movement*)this->_componentList["Movement"];
	movement->setVelocity(GVector2(0, 0));

	this->setStatus(NORMAL);
}

float Ridley::checkCollision(BaseObject* object, float dt)
{
	if (object->getStatus() == eStatus::DESTROY)
		return 0.0f;

	auto collisionBody = (CollisionBody*)_componentList["CollisionBody"];
	eID objectId = object->getId();
	eDirection direction;

	if (objectId == eID::WALL)
	{
		// Kiểm tra va chạm
		if (collisionBody->checkCollision(object, direction, dt, true))
		{
			// Nếu va chạm TOP mà trừ trường hợp nhảy lên vận tốc y lớn hơn 0
			// Trường hợp vận tốc y lớn hơn 0 là trường hợp nhảy lên
			if (direction == eDirection::TOP && !(this->getVelocity().y > 0 && this->isInStatus(eStatus::JUMPING)))
			{
				auto gravity = (Gravity*)this->_componentList["Gravity"];
				gravity->setStatus(eGravityStatus::SHALLOWED);

				this->stand();
				_preWall = object;
			}
		}
		else if (_preWall == object)
		{
			// Nếu đã đi ra khỏi hết Wall đụng trước đó thì cho rớt xuống
			auto gravity = (Gravity*)this->_componentList["Gravity"];
			gravity->setStatus(eGravityStatus::FALLING_DOWN);
		}
	}
}
