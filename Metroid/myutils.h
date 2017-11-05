#ifndef __MYUTIL_H__
#define __MYUTIL_H__

#include "define.h"
#include "pugixml/pugixml.hpp"
#include "BaseObject.h"
#include <list>
#include <ctime>

#include "Wall.h"

using namespace pugi;

map<string, string> GetObjectProperties(xml_node node);

BaseObject* GetObjectByType(xml_node item, eID type, int mapHeight);

list<BaseObject*>* GetListObjectFromFile(const string path);

#endif