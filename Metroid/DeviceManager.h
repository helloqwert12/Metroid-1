#ifndef __DEVICEMANAGER_H__
#define __DEVICEMANAGER_H__

#include "define.h"
#include "Graphics.h"

class DeviceManager
{
public:
	static DeviceManager* getInstance();

	void init(Graphics);

	void clearScreen();
	void present();

	LPDIRECT3DDEVICE9 getDevice();
	LPDIRECT3DSURFACE9 getSurface();

	static void release();
	~DeviceManager();

private:
	static DeviceManager* _instance;
	LPDIRECT3D9 _pD3d;
	LPDIRECT3DDEVICE9 _pDevice;
	LPDIRECT3DSURFACE9 _surface; // Để tạo back buffer

	DeviceManager();
};

#endif // !__DEVICEMANAGER_H__
