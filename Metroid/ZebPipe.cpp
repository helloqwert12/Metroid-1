#include "ZebPipe.h"
#include "SceneManager.h"
#include "PlayScene.h"

ZebPipe::ZebPipe(int x, int y, int width, int height) : BaseObject(ZEB_PIPE)
{
	this->_bound.left = x;
	this->_bound.bottom = y;
	this->_bound.top = y + height;
	this->_bound.right = x + width;

	_isActive = false;
}

void ZebPipe::init()
{
	this->_sprite = nullptr;
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;

	_zebAppearStopWatch = new StopWatch();
}

void ZebPipe::update(float deltatime)
{
	if (_isActive)
	{
		if (_zebAppearStopWatch->isStopWatch(ZEB_APPEAR_TIME))
		{
			// Lấy vị trí của Player
			auto playScene = (PlayScene*)SceneManager::getInstance()->getCurrentScene();
			auto playerPosition = playScene->getPlayer()->getPosition();

			Zeb* zeb = new Zeb((_bound.left + _bound.right) / 2, (_bound.top + _bound.bottom) / 2, playerPosition);
			zeb->init();
			QuadTreeNode::getInstance()->insert(zeb);
			//zeb = nullptr;
			_zebAppearStopWatch->restart();
		}
	}
}

void ZebPipe::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
}

void ZebPipe::release()
{
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();
}

GVector2 ZebPipe::getPosition()
{
	return GVector2(_bound.left, _bound.top);
}

void ZebPipe::setPosition(GVector2 position)
{
	_bound.left = position.x;
	_bound.top = position.y;
}

RECT ZebPipe::getBounding()
{
	return _bound;
}

void ZebPipe::active()
{
	_isActive = true;
}

void ZebPipe::deactive()
{
	_isActive = false;
}

bool ZebPipe::isActive()
{
	return _isActive;
}

float ZebPipe::checkCollision(BaseObject* object, float dt)
{
	return 0;
}
