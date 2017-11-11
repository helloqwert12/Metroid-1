#include "PlayScene.h"
#include "maputils.h"

PlayScene::PlayScene()
{
	_viewport = new Viewport(0, WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT);
}

PlayScene::~PlayScene()
{
	delete _viewport;
	_viewport = nullptr;
}

bool PlayScene::init()
{
	auto player = new Player();
	player->init();
	player->setPosition(1170, 600);
	player->getBounding();
	this->_player = player;

	_tileMap = TileMap::LoadFromFile("Resources//Maps//test.tmx", eID::MAP_METROID);

	_text = new Text(L"Arial", "", 10, 25);

	auto quadTreeWidth = (_tileMap->worldWidth() >= _tileMap->worldHeight()) ? _tileMap->worldWidth() : _tileMap->worldHeight();
	RECT rectMap;
	rectMap.left = 0;
	rectMap.bottom = 0;
	rectMap.top = quadTreeWidth;
	rectMap.right = quadTreeWidth;

	_root = new QuadTreeNode(rectMap);

	auto listObject = GetListObjectFromFile("Resources//Maps//test.tmx");

	for (auto obj : (*listObject))
	{
		_root->Insert(obj);
	}

	listObject->clear();
	return true;
}

void PlayScene::updateInput(float dt)
{
	this->getPlayer()->updateInput(dt);
}

void PlayScene::update(float dt)
{
	char str[100];
	sprintf(str, "Delta Time: %f", dt);
	_text->setText(str);

	if (this->checkEndGame())
	{
		return;
	}

	this->updateViewport(_player);

	RECT viewportInTransform = _viewport->getBounding();

	_root->DeleteObjects();

	_activeObject.clear();
	_activeObject = _root->Retrieve(viewportInTransform);
	_activeObject.push_back(_player);

	for (auto obj : _activeObject)
	{
		if (obj == nullptr || obj->isInStatus(eStatus::DESTROY) || obj->getId() == eID::WALL)
			continue;

		for (BaseObject* passiveObj : _activeObject)
		{
			if (passiveObj == nullptr || passiveObj == obj || passiveObj->isInStatus(eStatus::DESTROY))
				continue;
			obj->checkCollision(passiveObj, dt);
		}
	}

	for (BaseObject* obj : _activeObject)
	{
		obj->update(dt);
	}
}

void PlayScene::updateViewport(BaseObject* objTracker)
{
	GVector2 worldsize = this->_tileMap->getWorldSize();

	//GVector2 new_position = GVector2(max(objTracker->getPositionX() - 260, 0), WINDOW_HEIGHT);
	GVector2 new_position = GVector2(max(objTracker->getPositionX() - 260, 0), max(objTracker->getPositionY() + 400, 0));

	// Không cho đi quá map.
	if (new_position.x + WINDOW_WIDTH > worldsize.x)
	{
		new_position.x = worldsize.x - WINDOW_WIDTH;
	}

	_viewport->setPositionWorld(new_position);
}

void PlayScene::draw(LPD3DXSPRITE spriteHandle)
{
	_tileMap->draw(spriteHandle, _viewport);

	for (BaseObject* object : _activeObject)
	{
		object->draw(spriteHandle, _viewport);
	}

	_text->draw();
}

void PlayScene::release()
{
	_root->Release();
	SAFE_DELETE(_root);
	SAFE_DELETE(_tileMap);
}

bool PlayScene::checkEndGame()
{
	if (((Player*)_player)->getLifeNumber() < 0)
	{
		auto gameoverScene = new IntroScene();
		SceneManager::getInstance()->replaceScene(gameoverScene);
		return true;
	}

	return false;
}

BaseObject* PlayScene::getObject(eID id)
{
	if (id == eID::PLAYER)
		return getPlayer();

	eID objectID;
	if (_activeObject.size() == 0)
	{
		return nullptr;
	}

	for (BaseObject* object : _activeObject)
	{
		objectID = object->getId();
		if (objectID == id)
			return object;
	}

	return nullptr;
}

Player* PlayScene::getPlayer()
{
	return (Player*) this->_player;
}
