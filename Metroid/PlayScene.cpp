#include "PlayScene.h"
#include "maputils.h"

PlayScene::PlayScene()
{
	_viewport = new Viewport(0, WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT);
	_mapDirection = eMapDirection::HORIZONTAL;

	// Vị trí neo của viewport ban đầu
	_mapDirectionAnchorPoint = GVector2(896, 2468);
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
	player->setPosition(1170, 2500);
	player->getBounding();
	this->_player = player;

	_text = new Text(L"Tahoma", "", 445, 445, 22);

	// Tạo TileMap
	_tileMap = TileMap::LoadMapFromFile("Resources//Maps//map.tmx", eID::MAP_METROID);

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

	// Đọc file để lấy list các object
	auto listObject = GetListObjectFromFile("Resources//Maps//map.tmx");

	// Insert tất cả các object vào QuadTree
	for (auto object : (*listObject))
	{
		_root->insert(object);
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
	char str[50];
	sprintf(str, "FPS: %.0f", 1000 / dt);
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
	RECT viewportBounding = _viewport->getBounding();

	viewportBounding.left -= WINDOW_WIDTH / 2;
	viewportBounding.top +=  WINDOW_HEIGHT / 2;
	viewportBounding.right += WINDOW_WIDTH / 2;
	viewportBounding.bottom -= WINDOW_HEIGHT / 2;

	//viewportBounding.left -= WINDOW_WIDTH * 1.5;
	//viewportBounding.top +=  WINDOW_HEIGHT * 1.5;
	//viewportBounding.right += WINDOW_WIDTH * 1.5;
	//viewportBounding.bottom -= WINDOW_HEIGHT * 1.5;

	// Xóa các object đã bị DESTROY ra khỏi QuadTree
	_root->deleteObjects();

	_activeObject.clear();
	_activeObject = _root->retrieve(viewportBounding);

	// Kiểm tra va chạm player với các object
	for (BaseObject* object : _activeObject)
		_player->checkCollision(object, dt);

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

	for (BaseObject* object : _activeObject)
	{
		object->update(dt);
	}
}

void PlayScene::updateViewport(BaseObject* objectTracker)
{
	// Update tọa độ viewport theo vị trí Player và hướng Map
	GVector2 newPosition;
	if (_mapDirection == eMapDirection::HORIZONTAL) // hướng ngang
		newPosition = GVector2(objectTracker->getPositionX() - WINDOW_WIDTH / 2, _mapDirectionAnchorPoint.y + 400);
	else if (_mapDirection == eMapDirection::VERTICAL) // hướng dọc
		newPosition = GVector2(_mapDirectionAnchorPoint.x - 64, objectTracker->getPositionY() + 400);

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
		auto overScene = new IntroScene();
		SceneManager::getInstance()->replaceScene(overScene);
		return true;
	}

	return false;
}

Player* PlayScene::getPlayer()
{
	return (Player*) this->_player;
}

eMapDirection PlayScene::getMapDirection()
{
	return _mapDirection;
}

void PlayScene::setMapDirection(eMapDirection mapDirection, GVector2 mapDirectionAnchorPoint)
{
	_mapDirection = mapDirection;
	_mapDirectionAnchorPoint = mapDirectionAnchorPoint;
}
