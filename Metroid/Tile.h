#ifndef __TILE__
#define __TILE__

#include <string>
#include "Sprite.h"

// Class helper for class Map.
class Tile
{
private:
	int _id;
	RECT _srcRect;

	// ảnh gồm nhiều tile. khi vẽ cắt bằng srcRect như Sprite
	Sprite* _refSprite;

public:
	const int &getId() const;

	Tile(Sprite *refSprite, RECT srcRect, int id);
	void draw(LPD3DXSPRITE spriteHandle, GVector2 position, Viewport *viewport = NULL);
};

#endif	//#ifndef __TILE__
