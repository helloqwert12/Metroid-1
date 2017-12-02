#ifndef __MAPUTIL_H__
#define __MAPUTIL_H__

#include "define.h"
#include "pugixml/pugixml.hpp"
#include "BaseObject.h"
#include <ctime>
#include <list>

#include "Wall.h"
#include "ChangeMapDirection.h"
#include "AutoMoveViewport.h"
#include "Fire.h"

#include "BlueDoor.h"
#include "RedDoor.h"
#include "BreakableBlueWall.h"
#include "BreakableRedWall.h"
#include "BlueItemBall.h"
#include "RedItemBall.h"

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
list<BaseObject*>* getListObjectFromXML(const string path);

// Đọc tất cả properties của object từ 1 object node XML
map<string, string> getObjectProperties(xml_node node);

// Lấy object từ eID
BaseObject* getObjectById(eID id, int left, int top, int right, int bottom, int intArgument, GVector2 pointArgument);
BaseObject* getObjectById(xml_node item, eID type, int mapHeight);

// Object
BaseObject* getWall(xml_node item, int mapHeight);
BaseObject* getChangeMapDirection(xml_node item, int mapHeight);
BaseObject* getAutoMoveViewport(xml_node item, int mapHeight);
BaseObject* getFire(xml_node item, int mapHeight);
BaseObject* getBlueDoor(xml_node item, int mapHeight);
BaseObject* getRedDoor(xml_node item, int mapHeight);
BaseObject* getBreakableBlueWall(xml_node item, int mapHeight);
BaseObject* getBreakableRedWall(xml_node item, int mapHeight);
BaseObject* getBlueItemBall(xml_node item, int mapHeight);
BaseObject* getRedItemBall(xml_node item, int mapHeight);

// Enemy
BaseObject* getRipper(xml_node item, int mapHeight);
BaseObject* getWaver(xml_node item, int mapHeight);
BaseObject* getSkree(xml_node item, int mapHeight);
BaseObject* getMellow(xml_node item, int mapHeight);
BaseObject* getRio(xml_node item, int mapHeight);
BaseObject* getZebPipe(xml_node item, int mapHeight);
BaseObject* getZoomer(xml_node item, int mapHeight);

// Item
BaseObject* getEnergyTank(xml_node item, int mapHeight);
BaseObject* getEnergyBall(xml_node item, int mapHeight);
BaseObject* getMaruMari(xml_node item, int mapHeight);
BaseObject* getLongBeam(xml_node item, int mapHeight);
BaseObject* getIceBeam(xml_node item, int mapHeight);
BaseObject* getMissileRocketBall(xml_node item, int mapHeight);
BaseObject* getBombBall(xml_node item, int mapHeight);
BaseObject* getVaria(xml_node item, int mapHeight);

#endif // !__MAPUTIL_H__
