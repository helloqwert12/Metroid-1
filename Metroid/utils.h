#ifndef __UTILS_H__
#define __UTILS_H__

#include <d3dx9.h>
#include "define.h"
using namespace std;

// Kiểm tra 2 HCN có chồng lên nhau không.
// Dùng trong hệ world (x, y)
bool isIntersectedInGame(RECT rect1, RECT rect2);

// Tính khoảng cách giữa 2 điểm
float getDistance(D3DXVECTOR2 p1, D3DXVECTOR2 p2);

#endif // !__UTILS_H__
