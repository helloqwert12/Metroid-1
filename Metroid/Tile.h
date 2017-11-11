#ifndef __TILE__
#define __TILE__

#include <string>
#include "Sprite.h"

class Tile
{
private:
	int _id;
	RECT _srcRect;

	// Reference tới TileSet, khi vẽ cắt bằng srcRect như Sprite
	Sprite* _refSprite;

public:
	Tile(Sprite *refSprite, RECT srcRect, int id);

	void draw(LPD3DXSPRITE spriteHandle, GVector2 position, Viewport *viewport = NULL);

	// Lấy id của Tile
	int getId() const;
};

#endif	//#ifndef __TILE__
