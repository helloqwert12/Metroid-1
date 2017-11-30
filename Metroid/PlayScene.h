#ifndef __PLAYSCENE_H__
#define __PLAYSCENE_H__

#include "Scene.h"
#include "BaseObject.h"
#include "Text.h"
#include "TileMap.h"
#include "QuadTreeNode.h"
#include "Player.h"
#include <algorithm>
#include "SoundManager.h"
#include "IntroScene.h"
using namespace std;

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	bool init();
	void updateInput(float dt);
	void update(float dt);
	void draw(LPD3DXSPRITE spriteHandle);
	void release();

	Player* getPlayer();

	eMapDirection getMapDirection();
	void setMapDirection(eMapDirection mapDirection, GVector2 mapDirectionAnchorPoint);

private:
	Text* _text;
	TileMap* _tileMap;
	QuadTreeNode* _root;
	BaseObject* _player;

	// Hướng Map
	eMapDirection _mapDirection;
	GVector2 _mapDirectionAnchorPoint;

	// List chứa các object nằm trong viewport bound (Retrieve từ QuadTree)
	// Qua mỗi vòng lặp sẽ được update tại hàm update, và dùng để vẽ tại hàm draw
	vector<BaseObject*> _activeObject;

	// Update tọa độ viewport theo 1 object (chọn Player)
	void updateViewport(BaseObject* objectTracker);

	bool checkEndGame();
};

#endif // !__PLAYSCENE_H__
