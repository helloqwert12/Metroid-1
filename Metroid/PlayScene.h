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

[event_receiver(native)]
class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	bool init() override;
	void updateInput(float dt) override;
	void update(float dt) override;
	void draw(LPD3DXSPRITE spriteHandle) override;
	void release() override;

	BaseObject* getObject(eID id);

	Player* getPlayer();

private:
	Text* _text;

	TileMap* _tileMap;

	QuadTreeNode* _root;

	BaseObject* _player;

	// Danh sách đối tượng nằm trong vùng active.
	// Mỗi vòng lặp sẽ được kiểm tra chỉnh sửa tại update, và sử dụng lại tại draw.
	vector<BaseObject*> _activeObject;

	void updateViewport(BaseObject* objTracker);

	bool checkEndGame();
};

#endif // !__PLAYSCENE_H__
