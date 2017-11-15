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

	this->getPlayer()->resetValues();

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
	if (!_player->isInStatus(eStatus::DIE))
	{
		this->updateViewport(this->getPlayer());
	}

	// Lấy HCN bound của viewport
	RECT viewportInTransform = _viewport->getBounding();

	//viewportInTransform.left -= WINDOW_WIDTH / 2;
	//viewportInTransform.top +=  WINDOW_HEIGHT / 2;
	//viewportInTransform.right += WINDOW_WIDTH / 2;
	//viewportInTransform.bottom -= WINDOW_HEIGHT / 2;

	_root->deleteObjects();

	_activeObject.clear();
	_activeObject = _root->retrieve(viewportInTransform);

	// Kiểm tra va chạm player với các object
	for (BaseObject* obj : _activeObject)
		_player->checkCollision(obj, dt);

	// Xét va chạm từng object với các object còn lại
	int i = 0, j = 0;
	while (i < _activeObject.size() - 1)
	{
		j = i + 1;
		while (j < _activeObject.size())
		{
			if (_activeObject[i]->getId() == WALL) // Nếu là Wall thì xét va chạm object kia với Wall
				_activeObject[j]->checkCollision(_activeObject[i], dt);
			else // Nếu không phải là Wall thì xét va chạm bình thường
				_activeObject[i]->checkCollision(_activeObject[j], dt);
			j++;
		}
		i++;
	}

	// Update lại player và các object
	_player->update(dt);

	for (BaseObject* obj : _activeObject)
	{
		obj->update(dt);
	}
}

void PlayScene::updateViewport(BaseObject* objTracker)
{
	GVector2 worldsize = this->_tileMap->getWorldSize();

	//GVector2 newPosition = GVector2(max(objTracker->getPositionX() - 260, 0), WINDOW_HEIGHT);
	GVector2 newPosition = GVector2(max(objTracker->getPositionX() - WINDOW_WIDTH / 2, 0), max(objTracker->getPositionY() + 400, 0));

	_viewport->setPositionWorld(newPosition);
}

void PlayScene::draw(LPD3DXSPRITE spriteHandle)
{
	_tileMap->draw(spriteHandle, _viewport);

	for (BaseObject* object : _activeObject)
	{
		object->draw(spriteHandle, _viewport);
	}

	_player->draw(spriteHandle, _viewport);

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
