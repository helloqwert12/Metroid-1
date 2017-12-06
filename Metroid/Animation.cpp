#include "Animation.h"

Animation::Animation(Sprite* spriteSheet, float timeAnimate, bool loop)
{
	_spriteSheet = spriteSheet;
	_timeAnimate = timeAnimate;
	_canAnimate = true;
	_totalFrames = 0;

	_index = 0;
	_timer = 0;

	_startFrame = 0;
	_endFrame = _totalFrames - 1;

	this->setIndex(0);
	this->setLoop(loop);

	_canFlashes = false;
	_valueFlashes = 0.5f;
	_flashColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

Animation::~Animation()
{
}

void Animation::nextFrame()
{
	this->setIndex(_index + 1);
}

int Animation::getIndex()
{
	return _index;
}

void Animation::setIndex(int index)
{
	if (index == _index || _totalFrames == 0)
		return;

	_index = index;

	if (_index > _endFrame)
		_index = _startFrame;

	_currentRect = _frameRectList[_index];

	if (!_isLoop && _index == _endFrame)
	{
		this->stop();
	}
}

void Animation::update(float dt)
{
	if (!_canFlashes && !_canAnimate)
		return;

	// Do _timeAnimate tính bằng second nên chia 1000 để chuyển từ milisecond sang second
	_timer += dt / 1000;
	if (_timer >= _timeAnimate)
	{
		if (_canAnimate)
			this->nextFrame();

		_timer -= _timeAnimate;

		if (_canFlashes)
		{
			if (_spriteSheet->getOpacity() != _valueFlashes)
			{
				_spriteSheet->setOpacity(_valueFlashes);
				_spriteSheet->setColor(D3DXCOLOR(_flashColor.r, _flashColor.g, _flashColor.b, _valueFlashes));
			}
			else
			{
				_spriteSheet->setOpacity(1.0f);
				_spriteSheet->setColor(D3DXCOLOR(_flashColor.r, _flashColor.g, _flashColor.b, 1.0f));
			}
		}
	}
}

void Animation::draw(LPD3DXSPRITE spriteHandle)
{
	_spriteSheet->setFrameRect(_currentRect);
	_spriteSheet->render(spriteHandle);
}

void Animation::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	_spriteSheet->setFrameRect(_currentRect);
	_spriteSheet->render(spriteHandle, viewport);
}

float Animation::getTimeAnimate()
{
	return _timeAnimate;
}

void Animation::setTimeAnimate(float time)
{
	_timeAnimate = time;
}

void Animation::start()
{
	if (_canAnimate == false)
		_canAnimate = true;
}

void Animation::stop()
{
	if (_canAnimate == true)
		_canAnimate = false;
}

void Animation::canAnimate(bool can)
{
	if (_canAnimate != can)
		_canAnimate = can;
}

bool Animation::isAnimate()
{
	return _canAnimate;
}

void Animation::addFrameRect(RECT rect)
{
	// Nếu là rect đầu tiên thì set currentRect luôn
	if (_frameRectList.empty())
	{
		_currentRect = rect;
	}

	_frameRectList.push_back(rect);

	// Cập nhật lại totalFrames và endFrame
	_totalFrames = _frameRectList.size();
	_endFrame = _totalFrames - 1;
}

void Animation::addFrameRect(eID id, char* firstRectName, ...)
{
	va_list vl;
	char* rectName;

	va_start(vl, firstRectName);

	rectName = firstRectName;

	while (rectName != NULL)
	{
		this->addFrameRect(SpriteManager::getInstance()->getSourceRect(id, rectName));
		rectName = va_arg(vl, char*);
	}

	va_end(vl);
}

void Animation::setLoop(bool isLoop)
{
	if (isLoop != _isLoop)
		_isLoop = isLoop;
}

bool Animation::isLoop()
{
	return _isLoop;
}

void Animation::restart(int from)
{
	setIndex(from);

	if (_canAnimate == false)
		_canAnimate = true;
}

void Animation::enableFlashes(bool enable)
{
	if (_canFlashes == enable)
		return;

	_canFlashes = enable;
	_spriteSheet->setColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

void Animation::setValueFlashes(float value)
{
	if (_valueFlashes != value)
		_valueFlashes = value;
}

D3DXCOLOR Animation::getColorFlash()
{
	return _flashColor;
}

void Animation::setColorFlash(D3DXCOLOR color)
{
	_flashColor = color;
}
