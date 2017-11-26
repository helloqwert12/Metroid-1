#include "SpriteManager.h"
#include "pugixml/pugixml.hpp"
using namespace pugi;

SpriteManager* SpriteManager::_instance = nullptr;

SpriteManager* SpriteManager::getInstance()
{
	if (_instance == nullptr)
		_instance = new SpriteManager();
	return _instance;
}

SpriteManager::SpriteManager()
{
}

void SpriteManager::loadResource(LPD3DXSPRITE spriteHandle)
{
	Sprite* sprite = NULL;

	sprite = new Sprite(spriteHandle, L"Resources//Images//intro.png");
	sprite->setScale(SCALE_FACTOR);
	this->_listSprite[eID::INTRO_BACKGROUND] = sprite;

	sprite = new Sprite(spriteHandle, L"Resources//Images//font.png", 54, 6);
	sprite->setScale(SCALE_FACTOR);
	this->_listSprite[eID::FONT] = sprite;

	sprite = new Sprite(spriteHandle, L"Resources//Images//life.png");
	sprite->setScale(SCALE_FACTOR);
	this->_listSprite[eID::LIFE_ICON] = sprite;

	sprite = new Sprite(spriteHandle, L"Resources//Images//enegy.png");
	sprite->setScale(SCALE_FACTOR);
	this->_listSprite[eID::ENERGY_ICON] = sprite;

	sprite = new Sprite(spriteHandle, L"Resources//Images//player.png");
	sprite->setScale(SCALE_FACTOR);
	this->_listSprite.insert(pair<eID, Sprite*>(eID::PLAYER, sprite));
	this->loadSpriteInfo(eID::PLAYER, "Resources//Images//player.txt");

	sprite = new Sprite(spriteHandle, L"Resources//Images//enemy.png");
	sprite->setScale(SCALE_FACTOR);
	this->_listSprite.insert(pair<eID, Sprite*>(eID::ENEMY, sprite));
	this->loadSpriteInfo(eID::ENEMY, "Resources//Images//enemy.txt");
	
	sprite = new Sprite(spriteHandle, L"Resources//Images//bullet_effect.png");
	sprite->setScale(SCALE_FACTOR);
	this->_listSprite.insert(pair<eID, Sprite*>(eID::BULLET_EFFECT, sprite));
	this->loadSpriteInfo(eID::BULLET_EFFECT, "Resources//Images//bullet_effect.txt");

	sprite = new Sprite(spriteHandle, L"Resources//Images//item.png");
	sprite->setScale(SCALE_FACTOR);
	this->_listSprite.insert(pair<eID, Sprite*>(eID::ITEM, sprite));
	this->loadSpriteInfo(eID::ITEM, "Resources//Images//item.txt");

	// Load TileSet
	sprite = loadXMLDoc(spriteHandle, L"Resources//Maps//map.tmx");
	sprite->setOrigin(VECTOR2ZERO);
	sprite->setScale(SCALE_FACTOR);
	this->_listSprite[eID::MAP_METROID] = sprite;
}

Sprite* SpriteManager::loadXMLDoc(LPD3DXSPRITE spriteHandle, LPWSTR path)
{
	xml_document doc;
	xml_parse_result result = doc.load_file(path, parse_default | parse_pi);
	if (!result)
		return nullptr;

	auto tileset_node = doc.child("map").child("tileset");
	int tilecount = tileset_node.attribute("tilecount").as_int();
	int columns = tileset_node.attribute("columns").as_int();
	auto image = tileset_node.child("image");

	// Tìm tên file.
	// Cắt từ chuỗi path ra để tìm path thư mục.
	// Sau đó ghép với tên file ảnh được lấy từ file xml để load ảnh.
	string filename = image.attribute("source").as_string();		// lấy filename từ xml node
	wstring L_filename = wstring(filename.begin(), filename.end());	// convert to wstring.
	wstring strPath = wstring(path);								// convert to wstring.
	int index = strPath.find_last_of(L'//');						// cắt chuỗi để tìm path thư mục
	strPath = strPath.substr(0, index - 1);
	strPath += L"//" + L_filename;									// nối chuỗi

	return new Sprite(spriteHandle, (LPWSTR)strPath.c_str(), tilecount, columns);
}

Sprite* SpriteManager::getSprite(eID id)
{
	Sprite* it = this->_listSprite.find(id)->second;
	return new Sprite(*it);
}

RECT SpriteManager::getSourceRect(eID id, string name)
{
	return _sourceRectList[id][name];
}

void SpriteManager::loadSpriteInfo(eID id, const char* fileInfoPath)
{
	FILE* file;
	file = fopen(fileInfoPath, "r");

	if (file)
	{
		while (!feof(file))
		{
			RECT rect;
			char name[100];
			fgets(name, 100, file);

			fscanf(file, "%s %d %d %d %d", &name, &rect.left, &rect.top, &rect.right, &rect.bottom);

			_sourceRectList[id][string(name)] = rect;
		}
	}

	fclose(file);
}

void SpriteManager::release()
{
	delete _instance;
	_instance = nullptr;
}

SpriteManager::~SpriteManager()
{
	for (auto sprite = _listSprite.begin(); sprite != _listSprite.end(); ++sprite)
	{
		sprite->second->release(); // release Sprite's texture
		delete sprite->second; // delete Sprite
	}

	if (!_listSprite.empty())
		_listSprite.clear(); // Xóa hết con trỏ Sprite khỏi map
}
