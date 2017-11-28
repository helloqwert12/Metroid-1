#include "QuadTreeNode.h"

QuadTreeNode* QuadTreeNode::_instance = nullptr;

QuadTreeNode* QuadTreeNode::getInstance()
{
	return _instance;
}

void QuadTreeNode::setInstance(QuadTreeNode* root)
{
	_instance = root;
}

QuadTreeNode::QuadTreeNode(const RECT bound, int level)
{
	this->_bound = bound;
	this->_level = level;
	this->_children.reserve(4);
}

QuadTreeNode::~QuadTreeNode()
{
}

int QuadTreeNode::getIndex(const RECT& bound)
{
	// Tìm điểm chính giữa
	float midPointX = _bound.left + (_bound.right - _bound.left) / 2.0f;
	float midPointY = _bound.bottom + (_bound.top - _bound.bottom) / 2.0f;

	bool topQuadrant = (bound.bottom > midPointY);
	bool bottomQuadrant = (bound.top < midPointY);
	bool leftQuadrant = (bound.right < midPointX);
	bool rightQuadrant = (bound.left > midPointX);

	int index = -1;
	if (leftQuadrant)
	{
		if (topQuadrant)
		{
			index = 1;
		}
		else if (bottomQuadrant)
		{
			index = 2;
		}
	}
	else if (rightQuadrant)
	{
		if (topQuadrant)
		{
			index = 0;
		}
		else if (bottomQuadrant)
		{
			index = 3;
		}
	}

	// Nếu object nằm trong 2 không gian Node con trở lên thì return -1
	return index;
}

void QuadTreeNode::insert(BaseObject* object)
{
	// Kiểm tra xem object có nằm trong không gian của Node hiện tại hay không
	if (!isIntersectedInGame(this->_bound, object->getBounding()))
		return;

	// Nếu Node hiện tại đã được chia thành 4 Node con
	if (!_children.empty())
	{
		// Kiểm tra xem object nằm trong phần không gian của Node index thứ mấy và đệ quy Insert
		int index = getIndex(object->getBounding());
		if (index != -1)
		{
			_children[index]->insert(object);

			// Insert xong return ngay
			return;
		}
	}

	// Nếu Node hiện tại là Node lá (chưa được chia thành 4 Node con)
	// hoặc object nằm trong 2 không gian Node con trở lên
	// thì thêm object vào list object hiện tại
	_objects.push_back(object);

	// Nếu số object đã vượt quá mức quy định thì tiến hành đưa các object về 4 Node con
	if (_objects.size() > MAX_OBJECT && _level < MAX_LEVEL)
	{
		if (_children.empty())
			split(); // chia thành 4 Node con

		int i = 0;
		while (i < _objects.size())
		{
			int index = getIndex(_objects[i]->getBounding());
			if (index != -1)
			{
				_children[index]->insert(_objects[i]);

				// Insert vào Node con xong thì xóa object khỏi list object hiện tại
				_objects.erase(_objects.begin() + i);
			}
			else
			{
				i++;
			}
		}
	}
}

void QuadTreeNode::split()
{
	const float halfWidth = (_bound.right - _bound.left) / 2.0f;
	const float halfHeight = (_bound.top - _bound.bottom) / 2.0f;

	// Tính toán bound cho 4 Node con
	RECT rect;

	// Node phần không gian hình vuông index 0 (RIGHT-TOP)
	rect.left = _bound.left + halfWidth;
	rect.right = _bound.right;
	rect.bottom = _bound.bottom + halfHeight;
	rect.top = _bound.top;
	_children.push_back(new QuadTreeNode(rect, _level + 1));

	// Node phần không gian hình vuông index 1 (LEFT-TOP)
	rect.left = _bound.left;
	rect.right = _bound.left + halfWidth;
	_children.push_back(new QuadTreeNode(rect, _level + 1));

	// Node phần không gian hình vuông index 2 (LEFT-BOTTOM)
	rect.bottom = _bound.bottom;
	rect.top = _bound.bottom + halfHeight;
	_children.push_back(new QuadTreeNode(rect, _level + 1));

	// Node phần không gian hình vuông index 3 (RIGHT-BOTTOM)
	rect.left = _bound.left + halfWidth;
	rect.right = _bound.right;
	_children.push_back(new QuadTreeNode(rect, _level + 1));
}

vector<BaseObject*> QuadTreeNode::retrieve(const RECT viewportBound)
{
	vector<BaseObject*> foundObjects;

	// Kiểm tra HCN viewport nằm trong không gian Node nào
	int index = getIndex(viewportBound);
	if (!_children.empty() && index != -1)
	{
		// Đệ quy Retrieve tiếp ở Node đó
		foundObjects = _children[index]->retrieve(viewportBound);
	}
	else 	// Nếu Node hiện tại là Node lá (chưa được chia thành 4 Node con)
			// hoặc HCN viewport nằm trong 2 không gian Node con trở lên
	{
		for (auto child : _children)
		{
			// Kiểm tra HCN viewport có nằm trong không gian Node con không
			if (isIntersectedInGame(child->_bound, viewportBound))
			{
				// Đệ quy Retrieve tiếp ở Node con
				vector<BaseObject*> childObjects = child->retrieve(viewportBound);

				// Add range các object ở Node con
				foundObjects.insert(foundObjects.end(), childObjects.begin(), childObjects.end());
			}
		}
	}

	// Add range các object ở Node hiện tại
	foundObjects.insert(foundObjects.end(), _objects.begin(), _objects.end());

	return foundObjects;
}

void QuadTreeNode::deleteObjects()
{
	// Xóa các object đã bị DESTROY ra khỏi list object hiện tại
	if (!_objects.empty())
	{
		int i = 0;
		while (i < _objects.size())
		{
			// Nếu object có trạng thái DESTROY thì xóa khỏi list
			if (_objects[i]->getStatus() == eStatus::DESTROY)
			{
				auto object = _objects[i];
				_objects.erase(_objects.begin() + i);
				object->release();
				delete object;
			}
			else
				i++;
		}
	}

	// Gọi đệ quy xóa các object đã bị DESTROY ra khỏi các Node con
	if (!_children.empty())
		for (auto child : _children)
			child->deleteObjects();
}

void QuadTreeNode::writeQuadTreeNode(ofstream &fileOut, QuadTreeNode* node)
{
	if (node)
	{
		fileOut << node->_level << "\t\t";
		fileOut << node->_bound.left << "\t\t" << node->_bound.top << "\t\t" << node->_bound.right << "\t\t" << node->_bound.bottom << "\t\t";
		fileOut << node->_children.size() << "\t\t";
		fileOut << node->_objects.size() << "\t\t";

		for (auto object : node->_objects)
		{
			if (object->getId() == WALL || object->getId() == ZEB_PIPE) // Lấy bound left-top-right-bottom
			{
				fileOut << object->getId() << " ";
				fileOut << object->getBounding().left << " " << object->getBounding().top << " " << object->getBounding().right << " " << object->getBounding().bottom << "\t";
			}
			else if (object->getId() == CHANGE_MAP_DIRECTION) // Lấy bound left-top-right-bottom, mapDirection, MapDirectionAnchorPoint
			{
				fileOut << object->getId() << " ";
				fileOut << object->getBounding().left << " " << object->getBounding().top << " " << object->getBounding().right << " " << object->getBounding().bottom << " ";
				fileOut << ((ChangeMapDirection*)object)->getMapDirection() << " ";
				fileOut << ((ChangeMapDirection*)object)->getMapDirectionAnchorPoint().x << " " << ((ChangeMapDirection*)object)->getMapDirectionAnchorPoint().y << "\t";
			}
			else // lấy vị trí x, y
			{
				fileOut << object->getId() << " " << object->getPosition().x << " " << object->getPosition().y << "\t";
			}
		}

		fileOut << endl;
	}

	// Nếu có Node con thì gọi đệ quy để tiếp tục ghi
	if (!_children.empty())
	{
		for (auto child : node->_children)
			writeQuadTreeNode(fileOut, child);
	}
}

void QuadTreeNode::readQuadTreeFromFile(ifstream& fileIn)
{
	int level, left, top, right, bottom, numOfChildren, numOfObjects;
	fileIn >> level >> left >> top >> right >> bottom;
	fileIn >> numOfChildren >> numOfObjects;

	_level = level;
	_bound.left = left;
	_bound.top = top;
	_bound.right = right;
	_bound.bottom = bottom;

	for (int i = 0; i < numOfObjects; i++)
	{
		int objectId = 0, left = 0, top = 0, right = 0, bottom = 0;
		int mapDirection = 0;
		GVector2 mapDirectionAnchorPoint = GVector2(0, 0);

		fileIn >> objectId;

		if (objectId == WALL || objectId == ZEB_PIPE) // Lấy bound left-top-right-bottom
		{
			fileIn >> left >> top >> right >> bottom;
		}
		else if (objectId == CHANGE_MAP_DIRECTION) // Lấy bound left-top-right-bottom, mapDirection, MapDirectionAnchorPoint
		{
			fileIn >> left >> top >> right >> bottom >> mapDirection >> mapDirectionAnchorPoint.x >> mapDirectionAnchorPoint.y;
		}
		else // lấy vị trí x, y
		{
			fileIn >> left >> top;
		}

		BaseObject* object = GetObjectById((eID)objectId, left, top, right, bottom, (eMapDirection)mapDirection, mapDirectionAnchorPoint);
		if (object)
		{
			_objects.push_back(object);
		}
	}

	if (numOfChildren == 4)
	{
		RECT rect = { 0, 0, 0, 0 };
		_children.push_back(new QuadTreeNode(rect, _level + 1));
		_children.push_back(new QuadTreeNode(rect, _level + 1));
		_children.push_back(new QuadTreeNode(rect, _level + 1));
		_children.push_back(new QuadTreeNode(rect, _level + 1));

		for (auto child : _children)
		{
			child->readQuadTreeFromFile(fileIn);
		}
	}
}

void QuadTreeNode::release()
{
	if (!_objects.empty())
	{
		for (auto object : _objects)
		{
			object->release();
			SAFE_DELETE(object);
		}
	}

	if (!_children.empty())
	{
		for (auto child : _children)
		{
			child->release();
			SAFE_DELETE(child);
		}
	}
}
