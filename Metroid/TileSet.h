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
	Sprite *_tileImage; // Reference tới TileSet Image
	int _widthTile;  // Width của 1 Tile
	int _heightTile; // Height của 1 Tile

	vector<Tile*> _listTiles; // List chứa các Tile

public:
	TileSet(eID spriteId);

	int getWidthtile() const;
	void setWidthtile(const int &value);
	int getHeighttile() const;
	void setHeighttile(const int &value);

	// Đọc TileSet từ file XML
	void loadListTiles(xml_node& node);

	// Vẽ 1 ô Tile với id tương ứng. Gọi hàm này trong TileMap
	void draw(LPD3DXSPRITE spriteHandle, int id, GVector2 position, Viewport *viewport);
	
	Sprite* getSprite();
};

#endif // !__TILESET_H__
