#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "define.h"
#include "Viewport.h"

class Texture
{
public:
	Texture();
	~Texture();

	/*
		Load ảnh từ file và lưu vào LPDIRECT3DTEXTURE9
		@spriteHandle: DirectX sprite handle, dùng để load, vẽ sprite
		@filePath: đường dẫn đến file ảnh
		@color: back color
	*/
	HRESULT loadFromFile(LPD3DXSPRITE spriteHandle, LPWSTR filePath, D3DXCOLOR color = COLOR_WHITE, D3DXCOLOR colorkey = COLOR_KEY);

	/*
		Vẽ texture lên màn hình (thực chất là vẽ lên buffer)
		@spriteHandle: DirectX sprite handle, dùng để load, vẽ sprite
		@rect: phần HCN muốn vẽ (left, top, right, bottom)
		@center: center of frame to draw:
		- Nếu là NULL, top-left của ảnh sẽ được vẽ tại @position
		- Nếu là (x, y), top-left của ảnh sẽ được vẽ tại  @position - (x ,y)
		@postion: vị trí để vẽ
	*/
	void render(LPD3DXSPRITE spriteHandle, const RECT* rect, const GVector3* center, const GVector3* position);

	/*
	render texture với các tham số tranform, top-left
		@position: vị trí
		@scale: tỉ lệ scale
		@rotate: góc xoay theo độ (0-360)
		@origin: điểm neo để transform (gốc để transform)
		@zIndex: độ sâu
	*/
	void render(LPD3DXSPRITE spriteHandle, RECT* srcRect, GVector2 position, GVector2 scale, float rotate, GVector2 origin, float zIndex = 0);

	/*
	render texture với các tham số tranform, trong viewport
		@viewport: 
		@position: vị trí
		@scale: tỉ lệ scale
		@rotate: góc xoay theo độ (0-360)
		@origin: điểm neo để transform (gốc để transform)
		@zIndex: độ sâu
	*/
	void render(LPD3DXSPRITE spriteHandle, RECT* srcRect, Viewport viewport, GVector2 position, GVector2 scale, float rotate, GVector2 origin, float zIndex = 0);

	void setColor(D3DXCOLOR);
	D3DXCOLOR getColor();

	// Lấy width, height của ảnh
	int getWidth();
	int getHeight();

	void release();

private:
	LPDIRECT3DTEXTURE9	_texture;	// Dùng để chứa ảnh load từ file
	D3DXIMAGE_INFO		_imageInfo;	// Dùng để chứa thông tin file ảnh
	D3DXCOLOR			_color;		// Back color, khi vẽ sẽ được bỏ qua.
};

#endif // !__TEXTURE_H__
