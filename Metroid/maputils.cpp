#include "maputils.h"

list<BaseObject*>* GetListObjectFromFile(const string path)
{
	xml_document doc;
	list<BaseObject*>* listObject = new list<BaseObject*>();

	auto result = doc.load_file(path.data(), pugi::parse_default | pugi::parse_pi);
	if (result == false)
		return listObject;

	auto map = doc.child("map");
	if (map == NULL)
		return listObject;

	auto mapHeight = 2 * map.attribute("tileheight").as_int() * map.attribute("height").as_int();

	xml_node objectGroup = map.child("objectgroup");
	if (objectGroup == NULL)
		return listObject;

	auto objects = objectGroup.children();
	for (auto object : objects)
	{
		int id = object.attribute("id").as_int();
		auto type = object.attribute("type").as_int();

		eID enumID;
		try
		{
			enumID = (eID)type;
		}
		catch (exception e)
		{
			continue;
		}

		auto baseObject = GetObjectByType(object, enumID, mapHeight);
		if (baseObject != nullptr)
		{
			listObject->push_back(baseObject);
		}
	}

	return listObject;
}

map<string, string> GetObjectProperties(xml_node node)
{
	map<string, string> properties;

	// Lấy kích thước của object
	properties["x"] = node.attribute("x").as_string();
	properties["y"] = node.attribute("y").as_string();
	properties["width"] = node.attribute("width").as_string();
	properties["height"] = node.attribute("height").as_string();

	// Lấy các property của object
	auto params = node.child("properties");
	if (params)
	{
		for (auto item : params)
		{
			auto key = item.attribute("name").as_string();
			auto value = item.attribute("value").as_string();
			properties[key] = value;
		}
	}

	return properties;
}

BaseObject* GetObjectByType(xml_node item, eID type, int mapHeight)
{
	switch (type)
	{
	case WALL:
		return GetWall(item, mapHeight);
		break;
	case RIPPER:
		return GetRipper(item, mapHeight);
		break;
	case WAVER:
		return GetWaver(item, mapHeight);
		break;
	case SKREE:
		return GetSkree(item, mapHeight);
		break;
	case MELLOW:
		return GetMellow(item, mapHeight);
		break;
	case RIO:
		return GetRio(item, mapHeight);
		break;
	case ENERGY_TANK:
		return GetEnergyTank(item, mapHeight);
		break;
	case ENERGY_BALL:
		return GetEnergyBall(item, mapHeight);
		break;
	case MARU_MARI:
		return GetMaruMari(item, mapHeight);
		break;
	case LONG_BEAM:
		return GetLongBeam(item, mapHeight);
		break;
	case ICE_BEAM:
		return GetIceBeam(item, mapHeight);
		break;
	case MISSILE_ROCKET_BALL:
		return GetMissileRocketBall(item, mapHeight);
		break;
	case BOMB_BALL:
		return GetBombBall(item, mapHeight);
		break;
	case VARIA:
		return GetVaria(item, mapHeight);
		break;
	default:
		return nullptr;
	}
}

BaseObject* GetWall(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	// Do tọa độ được tạo từ Tiled Map Editor là top-left, nên ta chuyển về tọa độ world (x, y)
	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	auto wall = new Wall(x, y, width, height);
	wall->init();
	return wall;
}

BaseObject* GetRipper(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 2;

	auto ripper = new Ripper(x, y);
	ripper->init();
	return ripper;
}

BaseObject* GetWaver(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	auto waver = new Waver(x, y, false);
	waver->init();
	return waver;
}

BaseObject* GetSkree(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	auto skree = new Skree(x, y);
	skree->init();
	return skree;
}

BaseObject* GetMellow(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 2;

	auto mellow = new Mellow(x, y, false);
	mellow->init();
	return mellow;
}

BaseObject* GetRio(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	auto rio = new Rio(x, y, false);
	rio->init();
	return rio;
}

BaseObject* GetEnergyTank(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 2;

	auto energyTank = new EnergyTank(x, y);
	energyTank->init();
	return energyTank;
}

BaseObject* GetEnergyBall(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 2;

	auto energyBall = new EnergyBall(x, y);
	energyBall->init();
	return energyBall;
}

BaseObject* GetMaruMari(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 2;

	auto maruMari = new MaruMari(x, y);
	maruMari->init();
	return maruMari;
}

BaseObject* GetLongBeam(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 2;

	auto longBeam = new LongBeam(x, y);
	longBeam->init();
	return longBeam;
}

BaseObject* GetIceBeam(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 2;

	auto iceBeam = new IceBeam(x, y);
	iceBeam->init();
	return iceBeam;
}

BaseObject* GetMissileRocketBall(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 2;

	auto missileRocketBall = new MissileRocketBall(x, y);
	missileRocketBall->init();
	return missileRocketBall;
}

BaseObject* GetBombBall(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 2;

	auto bombBall = new BombBall(x, y);
	bombBall->init();
	return bombBall;
}

BaseObject* GetVaria(xml_node item, int mapHeight)
{
	auto properties = GetObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 2;

	auto varia = new Varia(x, y);
	varia->init();
	return varia;
}
