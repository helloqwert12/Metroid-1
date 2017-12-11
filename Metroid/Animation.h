#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "define.h"
#include "Sprite.h"
#include "Component.h"
#include "SpriteManager.h"
#include <vector>
#include <stdarg.h>

class Animation
{
public:
	/*
	Tạo Animation từ spritesheet
		@spriteSheet: spritesheet của animation
		@timeAnimate: thời gian chuyển từng frame
	Sau khi tạo bằng constructor này phải addFrameRect để có frame để chuyển động.
	*/
	Animation(Sprite* spriteSheet, float timeAnimate = 0.0f, bool loop = true);
	~Animation();

	// Chuyển qua frame kế tiếp
	void nextFrame();

	// Lấy giá trị frame index hiện tại
	int getIndex();

	// Set frame index cụ thể
	void setIndex(int index);

	// Update animation
	void update(float dt);

	// Vẽ animation
	void draw(LPD3DXSPRITE spriteHandle);
	void draw(LPD3DXSPRITE spriteHandle, Viewport* viewport);

	// Lấy giá trị thời gian chuyển frame
	float getTimeAnimate();

	// Set thời gian chuyển frame (lưu ý: thời gian tính theo giây)
	void setTimeAnimate(float time);

	// Bắt đầu chuyển frame
	void start();

	// Dừng chuyển frame
	void stop();

	void canAnimate(bool can);
	bool isAnimate();
	void addFrameRect(RECT rect);

	/*
	Add nhiều frameRect liên tiếp nhau, không giới hạn tham số, kết thúc bằng tham số NULL
		@id: ID của sprite
		@firstRectName,...: các tên của frameRect
	*/
	void addFrameRect(eID id, char* firstRectName, ...);

	void setLoop(bool isLoop);
	bool isLoop();

	// Chạy lại animation (@from: index frame muốn bắt đầu)
	void restart(int from = 0);

	// Tạo hiệu ứng chớp tắt cho sprite, sau khi set enable = TRUE, phải đặt giá trị thay đổi ở hàm setValueFlashes
	void enableFlashes(bool enable);

	// Set giá trị chớp tắt (@value: giá trị thay đổi để chớp, từ 0 đến < 1 (giá trị bình thường là 1))
	void setValueFlashes(float value);

	D3DXCOLOR getColorFlash();
	void setColorFlash(D3DXCOLOR color);

private:
	int _startFrame;
	int _endFrame;
	int _totalFrames;
	int _index;	// số index của frame

	float _timeAnimate;	// thời gian chuyển giữa các frame
	float _timer;

	bool _canAnimate;
	bool _isLoop;

	Sprite* _spriteSheet; // reference đến sprite
	vector<RECT> _frameRectList; // danh sách các frameRect
	RECT _currentRect; // frameRect hiện tại

	bool _canFlashes;
	float _valueFlashes;
	D3DXCOLOR _flashColor;
};

#endif // !__ANIMATION_H__
