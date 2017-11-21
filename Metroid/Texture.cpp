#include "Texture.h"
#include "DeviceManager.h"

Texture::Texture()
{
	_color = COLOR_WHITE;
	_texture = nullptr;
}

Texture::~Texture()
{
}

HRESULT Texture::loadFromFile(LPD3DXSPRITE spriteHandle, LPWSTR filePath, D3DXCOLOR color, D3DXCOLOR colorkey)
{
	HRESULT result;

	result = D3DXGetImageInfoFromFile(filePath, &this->_imageInfo);
	if (result != D3D_OK)
	{
		return result;
	}

	LPDIRECT3DDEVICE9 _device = DeviceManager::getInstance()->getDevice();
	spriteHandle->GetDevice(&_device);

	result = D3DXCreateTextureFromFileEx(
		_device,
		filePath,
		this->_imageInfo.Width,
		this->_imageInfo.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		colorkey,
		&this->_imageInfo,
		nullptr,
		&this->_texture);

	_color = color;

	return result;
}

void Texture::release()
{
	this->_texture->Release();
}

void Texture::render(LPD3DXSPRITE spriteHandle, RECT* srcRect, GVector2 position, GVector2 scale, float rotate, GVector2 origin, float zIndex)
{
	D3DXMATRIX matFinal;
	D3DXMATRIX matTransformed;
	D3DXMATRIX matOld;

	// Tính vị trí điểm neo (chính giữa) để vẽ
	// origin mặc định là (0.5f, 0.5f), set trong Sprite
	GVector3 center = GVector3(abs(srcRect->right - srcRect->left) * origin.x, abs(srcRect->top - srcRect->bottom) * (1 - origin.y), zIndex);
	
	// Lấy ma trận texture
	spriteHandle->GetTransform(&matOld);

	// Transform
	D3DXMatrixTransformation2D(
		&matTransformed,		// ma trận kết quả sau khi transform
		&position,				// điểm neo (scaling center)
		0.0f,
		&scale,					// tỉ lệ scale
		&position,				// điểm neo (rotaion center)
		D3DXToRadian(rotate),	// góc xoay (tính theo radian)
		0
	);

	// Nhân ma trận
	matFinal = matTransformed * matOld;

	// Set ma trận đã được transform
	spriteHandle->SetTransform(&matFinal);

	// Bắt đầu vẽ
	spriteHandle->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_DONOTSAVESTATE);

	spriteHandle->Draw(
		this->_texture,
		srcRect,
		&center,
		&GVector3(position.x, position.y, zIndex),
		_color);

	spriteHandle->SetTransform(&matOld);

	// Kết thúc vẽ
	spriteHandle->End();
}

void Texture::render(LPD3DXSPRITE spriteHandle, RECT* srcRect, Viewport viewport, GVector2 position, GVector2 scale, float rotate, GVector2 origin, float zIndex)
{
	GVector3 positionInViewport = viewport.getPositionInViewport(&GVector3(position.x, position.y, zIndex));

	render(spriteHandle, srcRect, GVector2((int)positionInViewport.x, (int)positionInViewport.y), scale, rotate, origin, positionInViewport.z);
}

void Texture::setColor(D3DXCOLOR color)
{
	this->_color = color;
}

D3DXCOLOR Texture::getColor()
{
	return _color;
}

int Texture::getWidth()
{
	return _imageInfo.Width;
}

int Texture::getHeight()
{
	return _imageInfo.Height;
}
