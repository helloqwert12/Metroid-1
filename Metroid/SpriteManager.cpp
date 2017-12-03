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
	this->_listSprite[eID::PLAYER] = sprite;
	this->loadSpriteInfo(eID::PLAYER, "Resources//Images//player.txt");

	sprite = new Sprite(spriteHandle, L"Resources//Images//enemy.png");
	sprite->setScale(SCALE_FACTOR);
	this->_listSprite[eID::ENEMY] = sprite;
	this->loadSpriteInfo(eID::ENEMY, "Resources//Images//enemy.txt");

	sprite = new Sprite(spriteHandle, L"Resources//Images//bullet_effect.png");
	sprite->setScale(SCALE_FACTOR);
	this->_listSprite[eID::BULLET_EFFECT] = sprite;
	this->loadSpriteInfo(eID::BULLET_EFFECT, "Resources//Images//bullet_effect.txt");

	sprite = new Sprite(spriteHandle, L"Resources//Images//item.png");
	sprite->setScale(SCALE_FACTOR);
	this->_listSprite[eID::ITEM] = sprite;
	this->loadSpriteInfo(eID::ITEM, "Resources//Images//item.txt");

	sprite = new Sprite(spriteHandle, L"Resources//Images//door.png");
	sprite->setScale(SCALE_FACTOR);
	this->_listSprite[eID::DOOR] = sprite;
	this->loadSpriteInfo(eID::DOOR, "Resources//Images//door.txt");

	sprite = new Sprite(spriteHandle, L"Resources//Images//breakable_wall.png");
	sprite->setScale(SCALE_FACTOR);
	this->_listSprite[eID::BREAKABLE_WALL] = sprite;
	this->loadSpriteInfo(eID::BREAKABLE_WALL, "Resources//Images//breakable_wall.txt");

	sprite = new Sprite(spriteHandle, L"Resources//Images//item_ball.png");
	sprite->setScale(SCALE_FACTOR);
	this->_listSprite[eID::ITEM_BALL] = sprite;
	this->loadSpriteInfo(eID::ITEM_BALL, "Resources//Images//item_ball.txt");

	sprite = new Sprite(spriteHandle, L"Resources//Images//boss_stage.png");
	sprite->setScale(SCALE_FACTOR);
	this->_listSprite[eID::BOSS_STAGE] = sprite;
	this->loadSpriteInfo(eID::BOSS_STAGE, "Resources//Images//boss_stage.txt");

	// Load TileSet
	sprite = loadTileSetFromXML(spriteHandle, L"Resources//Maps//map.tmx");
	sprite->setOrigin(VECTOR2ZERO);
	sprite->setScale(SCALE_FACTOR);
	this->_listSprite[eID::TILESET_METROID] = sprite;
}

Sprite* SpriteManager::loadTileSetFromXML(LPD3DXSPRITE spriteHandle, LPWSTR path)
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
	wstring L_filename = wstring(filename.begin(), filename.end());	// convert thành wstring.
	wstring strPath = wstring(path);								// convert thành wstring.
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

RECT SpriteManager::getSourceRect(eID id, string rectName)
{
	return _sourceRectList[id][rectName];
}

void SpriteManager::loadSpriteInfo(eID id, string fileInfoPath)
{
	ifstream fileIn;
	fileIn.open(fileInfoPath, ios::in);

	if (fileIn)
	{
		// Đọc dòng đầu tiên của file (title)
		string firstLine;
		getline(fileIn, firstLine);

		while (!fileIn.eof())
		{
			string rectName;
			RECT frameRect;

			fileIn >> rectName >> frameRect.left >> frameRect.top >> frameRect.right >> frameRect.bottom;

			_sourceRectList[id][rectName] = frameRect;
		}

		fileIn.close();
	}
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
