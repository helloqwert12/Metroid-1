#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "define.h"
#include "DeviceManager.h"
#include "Texture.h"
#include "Viewport.h"
#include "Transformable.h"
#include <list>
using namespace std;

class Sprite : public Transformable
{
public:
	/*
		@filePath: đường dẫn hình ảnh
		@totalFrames: số frame ảnh trên một file
		@cols: số frame trên một dòng
	Nếu không truyền số frame, số cột (mặc định = 1) thì sẽ vẽ hết hình
	Để vẽ một vị trí cụ thể trên hình thì dùng hàm setFrameRect()
	*/
	Sprite(LPD3DXSPRITE spriteHandle, LPWSTR filePath, int totalFrames = 1, int cols = 1);

	~Sprite();
	void release();

	void render(LPD3DXSPRITE spriteHandle);
	void render(LPD3DXSPRITE spriteHandle, Viewport* viewport);

	void setPosition(float x, float y);
	void setPosition(GVector2 position);
	void setPositionX(float x);
	void setPositionY(float y);

	void setScale(GVector2 scale);
	void setScale(float scale);
	void setScaleX(float scaleX);
	void setScaleY(float scaleY);

	void setRotate(float degree);
	void setOrigin(GVector2 origin);
	void setZIndex(float zIndex);

	RECT getBounding();

	void setFrameRect(RECT rect);
	RECT getFrameRect();

	// Lấy width, height của frame
	int getFrameWidth();
	int getFrameHeight();

	// Lấy width, height của nguyên tấm ảnh
	int getTextureWidth();
	int getTextureHeight();

	void setOpacity(float opacity);
	float getOpacity();

	// Màu vẽ sprite
	void setColor(D3DXCOLOR color);
	D3DXCOLOR getColor();

	// Set index frame cụ thể
	void setIndex(int index);

private:
	Texture _texture;

	float _opacity;	// từ 0.0f đến 1.0f
	D3DXCOLOR _color;

	RECT _bound;

	int _totalFrames; // tổng số frame
	int _columns; // số cột
	int _index;
	GVector2 _currentFrame; // frame hiện tại (cột, dòng)

	RECT _frameRect; // HCN muốn vẽ
	int _frameWidth;
	int _frameHeight;
	int _textureWidth;
	int _textureHeight;

	void setCurrentFrame();
	void setFrameRect();

	void updateBounding();
};

#endif // !__SPRITE_H__
