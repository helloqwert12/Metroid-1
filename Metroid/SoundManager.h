#ifndef __SOUNDMANAGER_H__
#define __SOUNDMANAGER_H__

#include "define.h"
#include "dxaudio.h"
#include <map>
#include <wincon.h>

using namespace std;
class SoundManager
{
public:
	~SoundManager();
	static SoundManager* getInstance();

	void loadSound(HWND hWnd);
	void play(eSoundID soundId);
	void stop(eSoundID soundId);
	void playLoop(eSoundID soundId);
	bool isPlaying(eSoundID soundId);

private:
	SoundManager();
	static SoundManager* _instance;
	map<eSoundID, CSound*> _listSound;
};

#endif // !__SOUNDMANAGER_H__
