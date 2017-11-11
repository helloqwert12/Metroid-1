#ifndef __HELP_H__
#define __HELP_H__

#include "StopWatch.h"
#include "TextSprite.h"
#include <vector>

[event_receiver(native)]
class Help : public IControlable
{
public:
	Help();
	~Help();

	void init();
	void update(float deltatime);
	void updateInput(float deltatime) override;
	void draw(LPD3DXSPRITE spriteHandle);

	void onKeyPressed(KeyEventArg* key_event);

private:
	vector<int> _stack_Key;
	float _radian;
	float _opacity;
	TextSprite* _message;
	void initStackKey();
};

#endif // !__HELP_H__
