#include "RightCannon.h"

RightCannon::RightCannon(int x, int y) : BaseObject(RIGHT_CANNON)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::BOSS_STAGE);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BOSS_STAGE, "cannon_05"));
	_sprite->setPosition(x, y);

	_spriteIndex = 0;
	_isActive = false;
}

void RightCannon::init()
{
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;

	_cannonBulletAppearStopWatch = new StopWatch();
}

void RightCannon::update(float deltatime)
{
	if (_isActive)
	{
		if (_cannonBulletAppearStopWatch->isStopWatch(CANNON_BULLET_APPEAR_TIME))
		{
			_spriteIndex++;
			if (_spriteIndex >= 8)
				_spriteIndex = 0;

			switch (_spriteIndex)
			{
			case 0:
				_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BOSS_STAGE, "cannon_05"));
				break;
			case 1:
				_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BOSS_STAGE, "cannon_06"));
				break;
			case 2:
				_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BOSS_STAGE, "cannon_07"));
				break;
			case 3:
				_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BOSS_STAGE, "cannon_08"));
				break;
			case 4:
				_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BOSS_STAGE, "cannon_01"));
				break;
			case 5:
				_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BOSS_STAGE, "cannon_08"));
				break;
			case 6:
				_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BOSS_STAGE, "cannon_07"));
				break;
			case 7:
				_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BOSS_STAGE, "cannon_06"));
				break;
			default:
				break;
			}

			if (_spriteIndex == 1 || _spriteIndex == 7)
			{
				auto cannonBulletPosition = GVector2(this->getPosition().x, this->getPosition().y);

				CannonBullet* cannonBullet = new CannonBullet(cannonBulletPosition.x, cannonBulletPosition.y, eID::RIGHT_CANNON);
				cannonBullet->init();
				QuadTreeNode::getInstance()->insert(cannonBullet);
			}

			_cannonBulletAppearStopWatch->restart();
		}
	}
}

void RightCannon::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	_sprite->render(spriteHandle, viewport);
}

void RightCannon::release()
{
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

void RightCannon::active()
{
	_isActive = true;
}

void RightCannon::deactive()
{
	_isActive = false;
}

bool RightCannon::isActive()
{
	return _isActive;
}

float RightCannon::checkCollision(BaseObject* object, float dt)
{
	return 0;
}
