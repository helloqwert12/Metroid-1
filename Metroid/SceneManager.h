#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include "define.h"
#include "Scene.h"
#include <vector>

class SceneManager
{
public:
	~SceneManager();
	static SceneManager* getInstance();

	bool init();
	void updateInput(float dt);
	void update(float dt);
	void draw(LPD3DXSPRITE spriteHandle);
	void release();

	void addScene(Scene* scene);
	void removeScene();
	void replaceScene(Scene* scene);
	void clearScenes();
	Scene* getCurrentScene();

private:
	SceneManager();
	static SceneManager* _instance;

	vector<Scene*> _scenes;
};

#endif // !__SCENEMANAGER_H__
