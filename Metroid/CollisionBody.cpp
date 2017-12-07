#include "CollisionBody.h"

CollisionBody::CollisionBody(BaseObject* target)
{
	_target = target;
}

CollisionBody::~CollisionBody()
{
}

bool CollisionBody::checkCollision(BaseObject* otherObject, eDirection& direction, float dt, bool isUpdatePosition)
{
	float time = isCollide(otherObject, direction, dt);

	if (time < 1.0f) // Nếu sẽ xảy ra va chạm
	{
		// Update tọa độ (cản lại)
		updateTargetPosition(otherObject, direction, true);

		return true;
	}
	else // Kiểm tra tiếp xem có đang va chạm rồi hay không
	{
		// Dùng để tạo GVector2 move(moveX, moveY) dùng để update lại tọa độ
		float moveX, moveY;

		// Kiểm tra tiếp xem có đang va chạm rồi hay không
		if (isColliding(otherObject, moveX, moveY, dt))
		{
			// Lấy hướng bị va chạm của otherObject
			auto side = this->getDirection(otherObject);
			direction = side;
			
			// Update tọa độ (dịch chuyển ra xa)
			if (isUpdatePosition)
				updateTargetPosition(otherObject, direction, false, GVector2(moveX, moveY));

			return true;
		}
	}

	direction = eDirection::NONE;
	return false;
}

float CollisionBody::isCollide(BaseObject* otherObject, eDirection& direction, float dt)
{
	RECT myRect = _target->getBounding();
	RECT otherRect = otherObject->getBounding();

	// Sử dụng Broadphase rect để kiểm tra trước vùng tiếp theo có va chạm không
	RECT broadphaseRect = getSweptBroadphaseRect(_target, dt);	// là bound của object được mở rộng ra thêm một phần bằng với vận tốc (dự đoán trước bound)
	if (!isColliding(broadphaseRect, otherRect))				// kiểm tra tính chồng lắp của 2 HCN
	{
		// Không va chạm trả về 1 đi tiếp bình thường
		direction = eDirection::NONE;
		return 1.0f;
	}

	// SweptAABB
	// Vận tốc mỗi frame
	GVector2 otherVelocity = GVector2(otherObject->getVelocity().x * dt / 1000, otherObject->getVelocity().y * dt / 1000);
	GVector2 myVelocity = GVector2(_target->getVelocity().x * dt / 1000, _target->getVelocity().y * dt / 1000);
	GVector2 velocity = myVelocity;

	// Nếu other object chuyển động thì dời vector vận tốc để trở thành 1 chuyển động, 1 đứng yên
	if (otherVelocity != GVector2(0, 0))
	{
		velocity = otherVelocity - myVelocity;
	}

	// Tính khoảng cách giữa cạnh gần nhất, xa nhất 2 object dx, dy
	// dx
	if (velocity.x > 0)
	{
		_dxEntry = otherRect.left - myRect.right;
		_dxExit = otherRect.right - myRect.left;
	}
	else
	{
		_dxEntry = otherRect.right - myRect.left;
		_dxExit = otherRect.left - myRect.right;
	}

	// dy
	if (velocity.y > 0)
	{
		_dyEntry = otherRect.bottom - myRect.top;
		_dyExit = otherRect.top - myRect.bottom;
	}
	else
	{
		_dyEntry = otherRect.top - myRect.bottom;
		_dyExit = otherRect.bottom - myRect.top;
	}

	// Tính thời gian va chạm 
	if (velocity.x == 0)
	{
		_txEntry = -std::numeric_limits<float>::infinity();
		_txExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		_txEntry = _dxEntry / velocity.x;
		_txExit = _dxExit / velocity.x;
	}

	if (velocity.y == 0)
	{
		_tyEntry = -std::numeric_limits<float>::infinity();
		_tyExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		_tyEntry = _dyEntry / velocity.y;
		_tyExit = _dyExit / velocity.y;
	}

	// Thời gian va chạm
	// Xảy ra va chạm khi x và y cùng chạm => thời gian va chạm trễ nhất giữa x và y
	float entryTime = max(_txEntry, _tyEntry);
	// Hết va chạm là 1 trong 2 x, y hết va chạm => thời gian sớm nhất để kết thúc va chạm
	float exitTime = min(_txExit, _tyExit);

	// Không xảy ra va chạm khi:
	// thời gian bắt đầu va chạm lớn hơn thời gian kết thúc va chạm
	// thời gian va chạm x, y nhỏ hơn 0 (2 object đang đi ra xa nhau)
	// thời gian va chạm x, y lớn hơn 1 (còn xa quá chưa thể va chạm)
	if (entryTime > exitTime || (_txEntry < 0.0f && _tyEntry < 0.0f) || _txEntry > 1.0f || _tyEntry > 1.0f)
	{
		// không va chạm trả về 1 đi tiếp bình thường
		direction = eDirection::NONE;
		return 1.0f;
	}

	// Nếu thời gian va chạm x lớn hơn y
	if (_txEntry > _tyEntry)
	{
		// Xét x
		// Khoảng cách gần nhất mà nhỏ hơn 0 nghĩa là object kia đang nằm bên trái object này => va chạm bên phải nó
		if (_dxEntry < 0.0f)
		{
			direction = eDirection::RIGHT;
		}
		else
		{
			direction = eDirection::LEFT;
		}
	}
	else // thời gian va chạm y lớn hơn x
	{
		// Xét y
		// Khoảng cách gần nhất mà nhỏ hơn 0 nghĩa là object kia đang nằm bên dưới object này => va chạm bên trên nó
		if (_dyEntry < 0.0f)
		{
			direction = eDirection::TOP;
		}
		else
		{
			direction = eDirection::BOTTOM;
		}
	}

	return entryTime;
}

bool CollisionBody::isColliding(BaseObject* otherObject, float& moveX, float& moveY, float dt)
{
	// Dùng để tạo GVector2 move(moveX, moveY) dùng để update lại tọa độ
	moveX = moveY = 0.0f;

	auto myRect = _target->getBounding();
	auto otherRect = otherObject->getBounding();

	float left = otherRect.left - myRect.right;
	float top = otherRect.top - myRect.bottom;
	float right = otherRect.right - myRect.left;
	float bottom = otherRect.bottom - myRect.top;

	// Kiểm tra xem có va chạm không
	// Có va chạm khi 
	// left <= 0 && right >= 0 && top >= 0 && bottom <= 0
	if (left > 0 || right < 0 || top < 0 || bottom > 0)
		return false;

	// Nếu có va chạm
	// Tính khoảng cách x, y để đi hết va chạm
	// Lấy khoảng cách nhỏ nhất
	// Do chỉ cần 1 cạnh hết va chạm thì va chạm sẽ kết thúc
	moveX = abs(left) < right ? left : right;
	moveY = top < abs(bottom) ? top : bottom;

	// Chỉ lấy phần lấn chồng lắp nhỏ nhất
	if (abs(moveX) < abs(moveY))
		moveY = 0.0f;
	else
		moveX = 0.0f;

	return true;
}

void CollisionBody::updateTargetPosition(BaseObject* otherObject, eDirection direction, bool withVelocity, GVector2 move)
{
	if (withVelocity) // cản lại khi va chạm
	{
		auto position = _target->getPosition();

		if (_txEntry > _tyEntry)
		{
			// Xử lý cản left và right
			if (_txEntry > 0 && _txEntry < 1)
				position.x += _dxEntry;
		}
		else
		{
			// Xử lý cản top và bottom
			if (_tyEntry > 0 && _tyEntry < 1)
				position.y += _dyEntry;
		}

		_target->setPosition(position);
	}
	else // dịch ra xa khi đang va chạm rồi
	{
		if (move.y > 0 && _target->getVelocity().y <= 0) // Va chạm TOP
		{
			_target->setPositionY(_target->getPositionY() + move.y);
		}
		else if (move.y < 0 && _target->getVelocity().y >= 0) // Va chạm BOTTOM
		{
			_target->setPositionY(_target->getPositionY() + move.y);
		}

		if (move.x > 0 && _target->getVelocity().x <= 0) // Va chạm RIGHT
		{
			_target->setPositionX(_target->getPositionX() + move.x);
		}
		else if (move.x < 0 && _target->getVelocity().x >= 0) // Va chạm LEFT
		{
			_target->setPositionX(_target->getPositionX() + move.x);
		}
	}
}

bool CollisionBody::isColliding(RECT myRect, RECT otherRect)
{
	float left = otherRect.left - myRect.right;
	float top = otherRect.top - myRect.bottom;
	float right = otherRect.right - myRect.left;
	float bottom = otherRect.bottom - myRect.top;

	return !(left > 0 || top < 0 || right < 0 || bottom > 0);
}

RECT CollisionBody::getSweptBroadphaseRect(BaseObject* object, float dt)
{
	// Vận tốc mỗi frame (vX, vY)
	auto velocity = GVector2(object->getVelocity().x * dt / 1000, object->getVelocity().y * dt / 1000);
	auto myRect = object->getBounding();

	RECT rect;
	rect.left = velocity.x > 0 ? myRect.left : myRect.left + velocity.x;
	rect.top = velocity.y > 0 ? myRect.top + velocity.y : myRect.top;
	rect.right = velocity.x > 0 ? myRect.right + velocity.x : myRect.right;
	rect.bottom = velocity.y > 0 ? myRect.bottom : myRect.bottom + velocity.y;

	return rect;
}

eDirection CollisionBody::getDirection(BaseObject* otherObject)
{
	auto myRect = _target->getBounding();
	auto otherRect = otherObject->getBounding();

	float left = otherRect.left - myRect.right;
	float top = otherRect.top - myRect.bottom;
	float right = otherRect.right - myRect.left;
	float bottom = otherRect.bottom - myRect.top;

	// Kiểm tra va chạm
	if (left > 0 || right < 0 || top < 0 || bottom > 0)
		return eDirection::NONE;

	float minX;
	float minY;
	eDirection sideY;
	eDirection sideX;

	if (top < abs(bottom))
	{
		minY = top;
		sideY = eDirection::TOP;
	}
	else
	{
		minY = bottom;
		sideY = eDirection::BOTTOM;
	}

	if (abs(left)< right)
	{
		minX = left;
		sideX = eDirection::LEFT;
	}
	else
	{
		minX = right;
		sideX = eDirection::RIGHT;
	}

	if (abs(minX) < abs(minY))
	{
		return sideX;
	}
	else
	{
		return sideY;
	}
}

void CollisionBody::update(float dt)
{
}
