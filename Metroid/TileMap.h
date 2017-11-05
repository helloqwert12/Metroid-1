#ifndef __TILEMAP_H__
#define __TILEMAP_H__

#include "TileSet.h"
#include "define.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "pugixml\pugixml.hpp"

using namespace std;
using namespace pugi;

class TileMap
{
public:

	void draw(LPD3DXSPRITE, Viewport*);
	void release();

	/*
	Load dữ liệu từ một file xml.
		path: file tiledmap xml được định nghĩa cấu trúc sẵn.
		eID: sprite id được đăng kí ở sprite manager.
	*/
	static TileMap* LoadFromFile(const string path, eID spriteId);

	// Lấy kich thước map.
	GVector2 getWorldSize();

	TileMap();
	~TileMap();

	int worldWidth();
	int worldHeight();
	
	int getCheckpoint();
	void setCheckpoint(int checkPoint);

	void setColor(D3DXCOLOR color);

private:

	int _frameWidth;	// độ rộng một frame (độ rộng của tile)
	int _frameHeight;	// độ cao một frame (độ cao của tile)

	int _checkPoint;

	// Kích thước map tính theo số ô Tile.
	GVector2 _mapSize;

	// Ma trận Tile id.
	// Id trong ma trận này được so sánh với Id của Tile trong TileSet.listTiles
	int** _mapIndex;

	// Chứa list tile.
	TileSet* _tileSet;

	/*
		[Function Helper]
		Đọc dữ liệu một mảng tile id
	*/
	void getElementMatrixIndex(xml_node& node);
};

#endif // !__TILEMAP_H__
