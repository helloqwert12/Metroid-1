#ifndef __QUADTREENODE_H__
#define __QUADTREENODE_H__

#include "define.h"
#include "BaseObject.h"
#include <algorithm>
#include <vector>
#include "maputils.h"

#define MAX_OBJECT 4
#define MAX_LEVEL 16

class QuadTreeNode
{
public:
	QuadTreeNode(const RECT bound, int level = 0);
	~QuadTreeNode();

	static QuadTreeNode* getInstance();
	static void setInstance(QuadTreeNode* root);

	// Insert 1 object vào Node
	void insert(BaseObject* object);

	// Lấy list các object có khả năng va chạm với viewport
	vector<BaseObject*> retrieve(const RECT viewportBound);

	// Xóa các object đã bị DESTROY ra khỏi list object hiện tại
	void deleteObjects();

	// Ghi QuadTree ra File
	void writeQuadTreeNode(ofstream &fileOut, QuadTreeNode* node);

	// Đọc QuadTree từ File
	void readQuadTreeFromFile(ifstream& fileIn);

	void release();

protected:
	static QuadTreeNode* _instance;

	int _level;
	RECT _bound;

	vector<QuadTreeNode*> _children; // list chứa 4 Node con
	vector<BaseObject*> _objects;	 // list chứa các object của Node hiện tại

									 // Kiểm tra xem HCN đang xét thuộc về phần hình vuông index thứ mấy (0-3)
	int getIndex(const RECT& bound);

	// Chia Node hiện tại thành 4 Node con
	void split();
};

#endif // !__QUADTREENODE_H__
