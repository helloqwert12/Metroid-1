#ifndef __TILESET__
#define __TILESET__

#include <string>
#include <vector>
#include <stdexcept>
#include "Tile.h"
#include "pugixml/pugixml.hpp"

class TileSet
{
private:
	Sprite *_tileImage;
	int _widthTile;  // width của 1 tile
	int _heightTile; // height của 1 tile

	vector<Tile*> _listTiles;	// List chứa các tile

public:
	TileSet(eID spriteId);

	int getWidthtile() const;
	void setWidthtile(const int &value);
	int getHeighttile() const;
	void setHeighttile(const int &value);

	// Đọc TileSet từ file XML
	void loadListTiles(pugi::xml_node& node);

	Sprite* getSprite();

	// Vẽ 1 ô tile tương ứng với id. Gọi hàm này trong TileMap
	void draw(LPD3DXSPRITE spriteHandle, int id, GVector2 position, Viewport *viewport);
};

#endif	//#ifndef __TILESET__
