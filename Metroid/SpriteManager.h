#ifndef __SPRITEMANAGER_H__
#define __SPRITEMANAGER_H__

#include "define.h"
#include "Sprite.h"
#include <map>
#include <fstream>

class SpriteManager
{
public:
	static SpriteManager* getInstance();

	void loadResource(LPD3DXSPRITE spriteHandle);

	Sprite* getSprite(eID id);
	RECT getSourceRect(eID id, string rectName);

	// Đọc file text để lấy danh sách sourceRect
	void loadSpriteInfo(eID id, string fileInfoPath);

	static void release();
	~SpriteManager();

private:
	SpriteManager();
	static SpriteManager* _instance;

	map<eID, Sprite*> _listSprite;
	map<eID, map<string, RECT>> _sourceRectList;

	// Đọc file xml để tạo đối tượng Sprite (là TileSet Image)
	Sprite* loadTileSetFromXML(LPD3DXSPRITE spriteHandle, LPWSTR path);
};

#endif // !__SPRITEMANAGER_H__
