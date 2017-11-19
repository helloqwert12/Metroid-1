#include "utils.h"

// Hệ world (x, y)
bool isIntersectedInGame(RECT rect1, RECT rect2)
{
	float left = rect1.left - rect2.right;
	float top = rect1.top - rect2.bottom;
	float right = rect1.right - rect2.left;
	float bottom = rect1.bottom - rect2.top;

	// Xét 2 trường hợp, rect1 so với rect2 và ngược lại, rect2 so với rect1
	if (left < 0 && top > 0 && right > 0 && bottom < 0)
		return true;

	if (left > 0 && top < 0 && right < 0 && bottom > 0)
		return true;

	return false;
}

float getDistance(D3DXVECTOR2 p1, D3DXVECTOR2 p2)
{
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}
