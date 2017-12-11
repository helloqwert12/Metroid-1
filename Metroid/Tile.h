#ifndef __TILE_H__
#define __TILE_H__

#include "Sprite.h"

// Dùng để lưu thông tin của 1 ô Tile (id và srcRect)
class Tile
{
private:
	int _id;
	RECT _srcRect;

	// Reference tới TileSet Image, khi vẽ cắt bằng srcRect như Sprite
	Sprite* _refSprite;

public:
	Tile(Sprite *refSprite, RECT srcRect, int id);

	void draw(LPD3DXSPRITE spriteHandle, GVector2 position, Viewport *viewport);

	// Lấy id của Tile
	int getId();
};

#endif // !__TILE_H__
