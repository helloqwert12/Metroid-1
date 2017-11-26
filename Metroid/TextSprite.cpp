#include "TextSprite.h"

TextSprite::TextSprite(string text, GVector2 position) : BaseObject(FONT)
{
	_sprite = SpriteManager::getInstance()->getSprite(FONT);
	_position = position;
	_text = text;
}

TextSprite::~TextSprite()
{
}

void TextSprite::init()
{
}

void TextSprite::update(float deltatime)
{
}

void TextSprite::draw(LPD3DXSPRITE spriteHandle)
{
	this->draw(spriteHandle, nullptr);
}

void TextSprite::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	int i = 0;
	int index = 0;

	// Sprite đánh thứ tự index theo 0-based
	for each (char c in this->_text)
	{
		if (c >= 'A' && c <= 'Z')
		{
			// Thứ tự của char kể từ 'A'
			// VD: A => index = 0; B => index = 1
			index = ((int)c) - 'A';
		}
		else if (c >= 'a' && c <= 'z')
		{
			index = ((int)c) - 'a';
		}
		else if (c >= '0' && c <= '9')
		{
			index = (((int)c) - '0') + 26;
		}
		else if (c == '.')
		{
			index = 36;
		}
		else if (c == '-')
		{
			index = 44;
		}
		else if (c == ':')
		{
			index = 45;
		}
		else if (c == ' ')
		{
			index = 53;
		}

		// Set index để lấy frameRect tương ứng muốn vẽ
		_sprite->setIndex(index);
		_sprite->setPosition(GVector2(_position.x + _sprite->getFrameWidth() * i, _position.y));

		// Render tọa độ top-left
		_sprite->render(spriteHandle);

		i++;
	}
}

void TextSprite::release()
{
}

GVector2 TextSprite::getPosition()
{
	return _position;
}

void TextSprite::setPosition(GVector2 position)
{
	_position = position;
}

void TextSprite::setText(string text)
{
	_text = text;
}
