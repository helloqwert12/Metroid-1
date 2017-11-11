#include "TileSet.h"
#include "Tile.h"
#include "SpriteManager.h"

TileSet::TileSet(eID spriteId)
{
	// Load TileSet Image
	Sprite* sp = SpriteManager::getInstance()->getSprite(spriteId);
	this->_tileImage = sp;
	this->_widthTile = sp->getFrameWidth();
	this->_heightTile = sp->getFrameHeight();
}

void TileSet::loadListTiles(pugi::xml_node& tileset)
{
	auto image = tileset.child("image");
	auto imageWidth = image.attribute("width").as_int();

	auto firstTileId = tileset.attribute("firstgid").as_int();
	auto tileWidth = tileset.attribute("tilewidth").as_int();
	auto tileHeight = tileset.attribute("tileheight").as_int();
	auto tileCount = tileset.attribute("tilecount").as_int();

	// Tính toán id (bắt đầu từ 1) và srcRect cho từng tile
	Tile* tile = nullptr;
	RECT srcRECT = { 0,0, tileWidth, tileHeight };

	while (tileCount--)
	{
		this->_listTiles.push_back(new Tile(this->_tileImage, srcRECT, firstTileId));
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

int TileSet::getWidthtile() const
{
	return _widthTile;
}

void TileSet::setWidthtile(const int &value)
{
	this->_widthTile = value;
}

int TileSet::getHeighttile() const
{
	return this->_heightTile;
}

void TileSet::setHeighttile(const int &value)
{
	this->_heightTile = value;
}

Sprite* TileSet::getSprite()
{
	return this->_tileImage;
}
