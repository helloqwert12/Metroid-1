#ifndef __MAPUTIL_H__
#define __MAPUTIL_H__

#include "define.h"
#include "pugixml/pugixml.hpp"
#include "BaseObject.h"
#include <list>
#include <ctime>

#include "Wall.h"

#include "Ripper.h"
#include "Waver.h"
#include "Skree.h"

#include "EnergyBall.h"
#include "LongBeam.h"
#include "IceBeam.h"
#include "MissileRocketBall.h"

using namespace pugi;

// Đọc danh sách các object từ file XML
list<BaseObject*>* GetListObjectFromFile(const string path);

// Đọc tất cả properties của object từ 1 object node XML
map<string, string> GetObjectProperties(xml_node node);

// Lấy object từ eID
BaseObject* GetObjectByType(xml_node item, eID type, int mapHeight);

// Object
BaseObject* GetWall(xml_node item, int mapHeight);

// Enemy
BaseObject* GetRipper(xml_node item, int mapHeight);
BaseObject* GetWaver(xml_node item, int mapHeight);
BaseObject* GetSkree(xml_node item, int mapHeight);

// Item
BaseObject* GetEnergyBall(xml_node item, int mapHeight);
BaseObject* GetLongBeam(xml_node item, int mapHeight);
BaseObject* GetIceBeam(xml_node item, int mapHeight);
BaseObject* GetMissileRocketBall(xml_node item, int mapHeight);

#endif // !__MAPUTIL_H__
