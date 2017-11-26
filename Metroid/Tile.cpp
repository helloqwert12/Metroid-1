#include "Tile.h"

Tile::Tile(Sprite *refSprite, RECT srcRect, int id)
{
	this->_id = id;
	this->_srcRect = srcRect;
	this->_refSprite = refSprite;
}

void Tile::draw(LPD3DXSPRITE spriteHandle, GVector2 position, Viewport *viewport)
{
	if (_refSprite == NULL)
		return;

	_refSprite->setPosition(position);
	_refSprite->setFrameRect(this->_srcRect);
	_refSprite->render(spriteHandle, viewport);
}

int Tile::getId()
{
	return this->_id;
}
