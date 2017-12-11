#ifndef __UTILS_H__
#define __UTILS_H__

#include "define.h"

// Dùng trong hệ world (x, y)
// Kiểm tra 2 HCN có chồng lên nhau không.
bool isIntersectedInGame(RECT rect1, RECT rect2);

// Tính khoảng cách giữa 2 điểm
float getDistance(D3DXVECTOR2 p1, D3DXVECTOR2 p2);

#endif // !__UTILS_H__
