#include "TileMap.h"

TileMap::TileMap()
{
	_tileMatrix = NULL;
}

TileMap::~TileMap()
{
}

TileMap* TileMap::LoadMapFromFile(const string path, eID spriteId)
{
	xml_document doc;

	// Mở file và đọc
	xml_parse_result result = doc.load_file(path.data(), parse_default | parse_pi);
	if (result == false)
	{
		return nullptr;
	}

	TileMap* tileMap = new TileMap();

	xml_node map = doc.child("map");
	if (map == NULL)
		return nullptr;

	// Đọc và tạo TileSet từ file XML
	xml_node tileset = map.child("tileset");
	tileMap->_tileSet = new TileSet(spriteId);
	tileMap->_tileSet->loadListTiles(tileset);

	// Lấy mapSize (kích thước Map tính theo số ô Tile (cột, dòng))
	xml_node layer = map.child("layer");
	tileMap->_mapSize.x = layer.attribute("width").as_int();
	tileMap->_mapSize.y = layer.attribute("height").as_int();

	// Khởi tạo mảng hai chiều.
	tileMap->_tileMatrix = new int*[int(tileMap->_mapSize.y)];
	for (int i = 0; i < tileMap->_mapSize.y; i++)
	{
		tileMap->_tileMatrix[i] = new int[(int)tileMap->_mapSize.x];
	}

	// Đọc danh sách các Tile ID từ file XML
	tileMap->loadTileMatrix(layer);

	// Lưu lại frameWidth, frameHeight của mỗi tile. Để phục vụ cho việc vẽ map.
	tileMap->_frameWidth = tileMap->_tileSet->getSprite()->getFrameWidth();
	tileMap->_frameHeight = tileMap->_tileSet->getSprite()->getFrameHeight();

	return tileMap;
}

void TileMap::loadTileMatrix(xml_node& node)
{
	auto elements = node.child("data").children();
	auto row = 0, col = 0;

	for (auto element : elements)
	{
		this->_tileMatrix[row][col] = element.attribute("gid").as_int();
		col++;
		if (col >= this->_mapSize.x)
		{
			col = 0;
			row++;
		}
	}
}

void TileMap::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	// Duyệt hết cả map phát sinh đển hàng ngàn lần vẽ
	// Nên ta kiểm tra toạ độ viewport để xác định cặp giá trị index i, j trước khi chạy vòng lặp for 2 lớp
	RECT screenRect =
	{
		viewport->getPositionWorld().x,
		viewport->getPositionWorld().y,
		viewport->getPositionWorld().x + viewport->getWidth(),
		viewport->getPositionWorld().y - viewport->getHeight()
	}; // top lớn hơn bottom (sử dụng hệ toạ độ x, y)

	int colBegin = max(screenRect.left / _frameWidth, 0);
	int colEnd = min(screenRect.right / _frameWidth + 1, _mapSize.x);
	int rowBegin = _mapSize.y - min(screenRect.top / _frameHeight + 1, _mapSize.y);
	int rowEnd = _mapSize.y - max(screenRect.bottom / _frameHeight, 0);
	// cộng thêm 1 vì cần có thêm một Tile vẽ tràn một phần ra khỏi màn hình.

	GVector2 position; // tọa độ world (x, y)
	for (int row = rowBegin; row < rowEnd; row++)
	{
		for (int col = colBegin; col < colEnd; col++)
		{
			// Tính toán vị trí vẽ Tile
			position.x = col * _frameWidth;
			position.y = (_mapSize.y - row - 1) * _frameHeight; // do row, col tính theo trục top-left
			this->_tileSet->draw(spriteHandle, this->_tileMatrix[row][col], position, viewport);
		}
	}
}

int TileMap::worldHeight()
{
	return _frameWidth * _mapSize.x;
}

int TileMap::worldWidth()
{
	return _frameHeight * _mapSize.y;
}

GVector2 TileMap::getWorldSize()
{
	GVector2 result;
	result.x = this->_frameWidth * this->_mapSize.x;
	result.y = this->_frameHeight * this->_mapSize.y;
	return result;
}
