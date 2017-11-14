#ifndef __INPUTCONTROLLER_H__
#define __INPUTCONTROLLER_H__

#include "define.h"
#include "Graphics.h"
#include "Event.h"
#include <vector>
#include "define.h"

#define KEYBOARD_BUFFER_SIZE 1024

class KeyEventArg : public EventArg
{
public:
	KeyEventArg(int keycode) 
	{ 
		this->keycode = keycode; 
	}

	int keycode;
};

[event_source(native)]
class InputController
{
public:
	~InputController();

	static InputController* getInstance();
	static void release();

	bool init(HWND, HINSTANCE); // Gọi hàm này trong Game::init()
	void update(); // Gọi hàm này trong game loop để update

	int isKeyDown(int keycode); // Kiểm tra phím có được nhấn không

	// Events
	__event void __eventkeyPressed(KeyEventArg* e);
	__event void __eventkeyReleased(KeyEventArg* e);

private:
	static InputController* _instance;
	
	LPDIRECTINPUT _input;
	LPDIRECTINPUTDEVICE8 _keyboard;
	BYTE _keyBuffer[256]; // DirectInput keyboard state buffer 
	HWND _hWnd; // Dùng để reference đến window (gửi Quit Message)

	// Buffered keyboard data
	DIDEVICEOBJECTDATA _keyEvents[KEYBOARD_BUFFER_SIZE];

	InputController();
};

#endif // !__INPUTCONTROLLER_H__
