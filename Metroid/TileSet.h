#ifndef __TILESET_H__
#define __TILESET_H__

#include <string>
#include <vector>
#include <stdexcept>
#include "Tile.h"
#include "pugixml/pugixml.hpp"
using namespace pugi;

// Dùng để lưu thông tin TileSet
class TileSet
{
private:
	Sprite *_tileImage; // reference tới TileSet Image
	vector<Tile*> _listTiles; // list chứa các Tile

public:
	TileSet(eID spriteId);

	// Đọc TileSet từ file XML
	void loadListTiles(xml_node& tileSet);

	// Vẽ 1 ô Tile với id tương ứng. Gọi hàm này trong TileMap
	void draw(LPD3DXSPRITE spriteHandle, int id, GVector2 position, Viewport *viewport);
	
	Sprite* getSprite();
};

#endif // !__TILESET_H__
