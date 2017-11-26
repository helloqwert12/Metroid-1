#ifndef __TEXTSPRITE_H__
#define __TEXTSPRITE_H__

#include "BaseObject.h"

class TextSprite : public BaseObject
{
public:
	TextSprite(string text, GVector2 position);
	~TextSprite();

	void init();
	void update(float deltatime);
	void draw(LPD3DXSPRITE spriteHandle);
	void draw(LPD3DXSPRITE spriteHandle, Viewport* viewport);
	void release();

	GVector2 getPosition();
	void setPosition(GVector2 position);

	void setText(string text);

private:
	string _text;
	GVector2 _position; // tọa độ top-left
};

#endif // !__TEXTSPRITE_H__
