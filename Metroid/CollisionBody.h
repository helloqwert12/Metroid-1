#ifndef __COLLISIONBODY_H__
#define __COLLISIONBODY_H__

#include "BaseObject.h"
#include "Component.h"

// Hệ tọa độ World (x, y)
class CollisionBody : public Component
{
public:
	CollisionBody(BaseObject* target);
	~CollisionBody();

	/*
	Kiểm tra va chạm với object khác, lấy được hướng bị va chạm
		@otherObject: object cần kiểm tra va chạm
		@direction: lấy hướng bị va chạm của otherObject
		@dt: deltatime của mỗi frame
		@isUpdatePosition: TRUE khi muốn CollisionBody sẽ cập nhật vị trí object lại nếu object này đang chồng lắp lên object khác
	*/
	bool checkCollision(BaseObject* otherObject, eDirection& direction, float dt, bool isUpdatePosition = true);

	// Kiểm tra va chạm và trả về thời gian bắt đầu va chạm và hướng va chạm (SweptAABB)
	float isCollide(BaseObject* otherObject, eDirection& direction, float dt);

	// Kiểm tra có đang va chạm rồi hay không, trả về khoảng chồng lắp nhỏ nhất
	bool isColliding(BaseObject* otherObject, float& moveX, float& moveY, float dt);

	// Kiểm tra 2 HCN có đang chồng lắp nhau hay không (AABB)
	bool isColliding(RECT myRect, RECT otherRect);

	// Lấy Broadphase rect để kiểm tra trước vùng tiếp theo có va chạm không
	RECT getSweptBroadphaseRect(BaseObject* object, float dt);

	// Lấy hướng bị va chạm của otherObject
	eDirection getDirection(BaseObject* otherObject);

	/*
	Cập nhật target position khi va chạm
		@otherObject: đối tượng va chạm
		@direction: hướng bị va chạm của otherObject
		@withVelocity:	TRUE khi kiểm va chạm với vận tốc, tham số move không cần. 
						FALSE khi va chạm bằng kiểm tra RECT, cần tham số move
		@move: khoảng chồng lấp nhỏ nhất của 2 object, dùng làm vector vận tốc để dịch chuyển ra xa
	*/
	void updateTargetPosition(BaseObject* otherObject, eDirection direction, bool withVelocity, GVector2 move = GVector2(0, 0));

	void update(float dt);

private:
	BaseObject* _target; // Reference tới object chứa CollisionBody này

	float _dxEntry, _dyEntry, _dxExit, _dyExit;
	float _txEntry, _tyEntry, _txExit, _tyExit;
};

#endif // !__COLLISIONBODY_H__
