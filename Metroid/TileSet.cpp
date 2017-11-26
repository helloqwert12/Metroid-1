#include "TileSet.h"
#include "Tile.h"
#include "SpriteManager.h"

TileSet::TileSet(eID spriteId)
{
	// Load TileSet Image
	Sprite* sprite = SpriteManager::getInstance()->getSprite(spriteId);
	this->_tileImage = sprite;
}

void TileSet::loadListTiles(xml_node& tileSet)
{
	auto image = tileSet.child("image");
	auto imageWidth = image.attribute("width").as_int();

	auto firstTileId = tileSet.attribute("firstgid").as_int();
	auto tileWidth = tileSet.attribute("tilewidth").as_int();
	auto tileHeight = tileSet.attribute("tileheight").as_int();
	auto tileCount = tileSet.attribute("tilecount").as_int();

	// Tính toán id (bắt đầu từ 1) và srcRect cho từng tile
	Tile* tile = nullptr;
	RECT srcRECT = { 0,0, tileWidth, tileHeight };

	// Thêm từng Tile vào listTiles
	while (tileCount--)
	{
		this->_listTiles.push_back(new Tile(this->_tileImage, srcRECT, firstTileId));

		// Tính toán srcRect cho Tile
		firstTileId++;
		if (srcRECT.right + tileWidth > imageWidth)
		{
			srcRECT.left = 0;
			srcRECT.top += tileHeight;
		}
		else
			srcRECT.left += tileWidth;

		srcRECT.right = srcRECT.left + tileWidth;
		srcRECT.bottom = srcRECT.top + tileHeight;
	}
}

void TileSet::draw(LPD3DXSPRITE spriteHandle, int id, GVector2 position, Viewport *viewport)
{
	for (auto tile : _listTiles)
	{
		if (tile->getId() == id)
		{
			tile->draw(spriteHandle, position, viewport);
			return;
		}
	}
}

Sprite* TileSet::getSprite()
{
	return this->_tileImage;
}
