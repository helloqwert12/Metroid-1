﻿#ifndef __MAPUTIL_H__
#define __MAPUTIL_H__

#include "define.h"
#include "pugixml/pugixml.hpp"
#include "BaseObject.h"
#include <ctime>
#include <list>

#include "Wall.h"
#include "ChangeMapDirection.h"
#include "BlueDoor.h"
#include "RedDoor.h"

#include "Ripper.h"
#include "Waver.h"
#include "Skree.h"
#include "Mellow.h"
#include "Rio.h"
#include "ZebPipe.h"
#include "Zoomer.h"

#include "EnergyTank.h"
#include "EnergyBall.h"
#include "MaruMari.h"
#include "LongBeam.h"
#include "IceBeam.h"
#include "MissileRocketBall.h"
#include "BombBall.h"
#include "Varia.h"
using namespace pugi;

// Đọc danh sách các object từ file XML
list<BaseObject*>* GetListObjectFromXML(const string path);

// Đọc tất cả properties của object từ 1 object node XML
map<string, string> GetObjectProperties(xml_node node);

// Lấy object từ eID
BaseObject* GetObjectById(eID id, int left, int top, int right, int bottom, eMapDirection mapDirection, GVector2 mapDirectionAnchorPoint);
BaseObject* GetObjectById(xml_node item, eID type, int mapHeight);

// Object
BaseObject* GetWall(xml_node item, int mapHeight);
BaseObject* GetChangeMapDirection(xml_node item, int mapHeight);
BaseObject* GetBlueDoor(xml_node item, int mapHeight);
BaseObject* GetRedDoor(xml_node item, int mapHeight);

// Enemy
BaseObject* GetRipper(xml_node item, int mapHeight);
BaseObject* GetWaver(xml_node item, int mapHeight);
BaseObject* GetSkree(xml_node item, int mapHeight);
BaseObject* GetMellow(xml_node item, int mapHeight);
BaseObject* GetRio(xml_node item, int mapHeight);
BaseObject* GetZebPipe(xml_node item, int mapHeight);
BaseObject* GetZoomer(xml_node item, int mapHeight);

// Item
BaseObject* GetEnergyTank(xml_node item, int mapHeight);
BaseObject* GetEnergyBall(xml_node item, int mapHeight);
BaseObject* GetMaruMari(xml_node item, int mapHeight);
BaseObject* GetLongBeam(xml_node item, int mapHeight);
BaseObject* GetIceBeam(xml_node item, int mapHeight);
BaseObject* GetMissileRocketBall(xml_node item, int mapHeight);
BaseObject* GetBombBall(xml_node item, int mapHeight);
BaseObject* GetVaria(xml_node item, int mapHeight);

#endif // !__MAPUTIL_H__
