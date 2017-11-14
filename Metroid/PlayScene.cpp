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
	player->setPosition(1170, 2550);
	player->getBounding();
	this->_player = player;

	_text = new Text(L"Arial", "", 10, 25);

	// Tạo TileMap
	_tileMap = TileMap::LoadFromFile("Resources//Maps//map.tmx", eID::MAP_METROID);

	// Lấy kích thước của QuadTree (do QuadTree hình vuông nên ta lấy cạnh lớn nhất)
	auto quadTreeWidth = (_tileMap->worldWidth() >= _tileMap->worldHeight()) ? _tileMap->worldWidth() : _tileMap->worldHeight();
	RECT rectMap;
	rectMap.left = 0;
	rectMap.top = quadTreeWidth;
	rectMap.right = quadTreeWidth;
	rectMap.bottom = 0;

	// Tạo QuadTree
	_root = new QuadTreeNode(rectMap);
	QuadTreeNode::setInstance(_root);

	auto listObject = GetListObjectFromFile("Resources//Maps//map.tmx");

	// Insert tất cả các object vào QuadTree
	for (auto obj : (*listObject))
	{
		_root->insert(obj);
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
	sprintf(str, "Delta Time: %0.2f", dt);
	_text->setText(str);

	if (this->checkEndGame())
	{
		return;
	}

	// Update viewport theo object tracker là Player
	this->updateViewport(_player);

	// Lấy HCN bound của viewport
	RECT viewportInTransform = _viewport->getBounding();

	_root->deleteObjects();

	_activeObject.clear();
	_activeObject = _root->retrieve(viewportInTransform);
	_activeObject.push_back(_player);

	for (auto obj : _activeObject)
	{
		// Nếu object đã bị DESTROY hoặc object là Wall thì bỏ qua
		if (obj == nullptr || obj->isInStatus(eStatus::DESTROY) || obj->getId() == eID::WALL)
			continue;

		// Xét va chạm từng object với các object còn lại
		for (BaseObject* passiveObj : _activeObject)
		{
			// Nếu object đang xét là chính nó hoặc object đã bị DESTROY thì bỏ qua
			if (passiveObj == nullptr || passiveObj == obj || passiveObj->isInStatus(eStatus::DESTROY))
				continue;

			// Kiểm tra va chạm
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
	_root->release();
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

Player* PlayScene::getPlayer()
{
	return (Player*) this->_player;
}
