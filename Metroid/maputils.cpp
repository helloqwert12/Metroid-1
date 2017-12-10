#include "maputils.h"

list<BaseObject*>* getListObjectFromXML(const string path)
{
	xml_document doc;
	list<BaseObject*>* listObject = new list<BaseObject*>();

	auto result = doc.load_file(path.data(), pugi::parse_default | pugi::parse_pi);
	if (result == false)
		return listObject;

	auto map = doc.child("map");
	if (!map)
		return listObject;

	auto mapHeight = 2 * map.attribute("tileheight").as_int() * map.attribute("height").as_int();

	xml_node objectGroup = map.child("objectgroup");
	if (!objectGroup)
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

		auto baseObject = getObjectById(object, enumID, mapHeight);
		if (baseObject != nullptr)
		{
			listObject->push_back(baseObject);
		}
	}

	return listObject;
}

map<string, string> getObjectProperties(xml_node node)
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

BaseObject* getObjectById(eID id, int left, int top, int right, int bottom, int intArgument, GVector2 pointArgument)
{
	switch (id)
	{
	case WALL:
	{
		auto wall = new Wall(left, bottom, right - left, top - bottom);
		wall->init();
		return wall;
		break;
	}
	case CHANGE_MAP_DIRECTION:
	{
		auto mapDirection = (eMapDirection)intArgument;
		auto mapDirectionAnchorPoint = pointArgument;
		auto changeMapDirection = new ChangeMapDirection(left, bottom, right - left, top - bottom, mapDirection, mapDirectionAnchorPoint);
		changeMapDirection->init();
		return changeMapDirection;
		break;
	}
	case AUTO_MOVE_VIEWPORT:
	{
		auto autoMoveViewport = new AutoMoveViewport(left, bottom, right - left, top - bottom);
		autoMoveViewport->init();
		return autoMoveViewport;
		break;
	}
	case FIRE:
	{
		auto fire = new Fire(left, bottom, right - left, top - bottom);
		fire->init();
		return fire;
		break;
	}
	case BLUE_DOOR:
	{
		auto blueDoor = new BlueDoor(left, top);
		blueDoor->init();
		return blueDoor;
		break;
	}
	case RED_DOOR:
	{
		auto redDoor = new RedDoor(left, top);
		redDoor->init();
		return redDoor;
		break;
	}
	case BREAKABLE_BLUE_WALL:
	{
		auto breakableBlueWall = new BreakableBlueWall(left, top);
		breakableBlueWall->init();
		return breakableBlueWall;
		break;
	}
	case BREAKABLE_RED_WALL:
	{
		auto breakableRedWall = new BreakableRedWall(left, top);
		breakableRedWall->init();
		return breakableRedWall;
		break;
	}
	case BLUE_ITEM_BALL:
	{
		auto itemId = (eID)intArgument;
		auto blueItemBall = new BlueItemBall(left, top, itemId);
		blueItemBall->init();
		return blueItemBall;
		break;
	}
	case RED_ITEM_BALL:
	{
		auto itemId = (eID)intArgument;
		auto redItemBall = new RedItemBall(left, top, itemId);
		redItemBall->init();
		return redItemBall;
		break;
	}
	case RIPPER:
	{
		auto ripper = new Ripper(left, top);
		ripper->init();
		return ripper;
		break;
	}
	case WAVER:
	{
		auto waver = new Waver(left, top, false);
		waver->init();
		return waver;
		break;
	}
	case SKREE:
	{
		auto skree = new Skree(left, top);
		skree->init();
		return skree;
		break;
	}
	case MELLOW:
	{
		auto mellow = new Mellow(left, top, false);
		mellow->init();
		return mellow;
		break;
	}
	case RIO:
	{
		auto rio = new Rio(left, top, false);
		rio->init();
		return rio;
		break;
	}
	case ZEB_PIPE:
	{
		auto zebPipe = new ZebPipe(left, bottom, right - left, top - bottom);
		zebPipe->init();
		return zebPipe;
		break;
	}
	case ZOOMER:
	{
		auto zoomer = new Zoomer(left, top);
		zoomer->init();
		return zoomer;
		break;
	}
	case ZEEBETITE:
	{
		auto zeebetite = new Zeebetite(left, top);
		zeebetite->init();
		return zeebetite;
		break;
	}
	case METROID:
	{
		auto metroid = new Metroid(left, top, false);
		metroid->init();
		return metroid;
		break;
	}
	case MOTHER_BRAIN:
	{
		auto motherBrain = new MotherBrain(left, top);
		motherBrain->init();
		return motherBrain;
		break;
	}
	case RINKA_CANNON:
	{
		auto rinkaCannon = new RinkaCannon(left, bottom, right - left, top - bottom);
		rinkaCannon->init();
		return rinkaCannon;
		break;
	}
	case LEFT_CANNON:
	{
		auto leftCannon = new LeftCannon(left, top);
		leftCannon->init();
		return leftCannon;
		break;
	}
	case MIDDLE_CANNON:
	{
		auto middleCannon = new MiddleCannon(left, top);
		middleCannon->init();
		return middleCannon;
		break;
	}
	case RIGHT_CANNON:
	{
		auto rightCannon = new RightCannon(left, top);
		rightCannon->init();
		return rightCannon;
		break;
	}
	case RIDLEY:
	{
		auto ridley = new Ridley(left, top);
		ridley->init();
		return ridley;
		break;
	}
	case ENERGY_TANK:
	{
		auto energyTank = new EnergyTank(left, top);
		energyTank->init();
		return energyTank;
		break;
	}
	case ENERGY_BALL:
	{
		auto energyBall = new EnergyBall(left, top);
		energyBall->init();
		return energyBall;
		break;
	}
	case MARU_MARI:
	{
		auto maruMari = new MaruMari(left, top);
		maruMari->init();
		return maruMari;
		break;
	}
	case LONG_BEAM:
	{
		auto longBeam = new LongBeam(left, top);
		longBeam->init();
		return longBeam;
		break;
	}
	case ICE_BEAM:
	{
		auto iceBeam = new IceBeam(left, top);
		iceBeam->init();
		return iceBeam;
		break;
	}
	case MISSILE_ROCKET_BALL:
	{
		auto missileRocketBall = new MissileRocketBall(left, top);
		missileRocketBall->init();
		return missileRocketBall;
		break;
	}
	case BOMB_BALL:
	{
		auto bombBall = new BombBall(left, top);
		bombBall->init();
		return bombBall;
		break;
	}
	case VARIA:
	{
		auto varia = new Varia(left, top);
		varia->init();
		return varia;
		break;
	}
	default:
		return nullptr;
	}
}

BaseObject* getObjectById(xml_node item, eID id, int mapHeight)
{
	switch (id)
	{
	case WALL:
		return getWall(item, mapHeight);
		break;
	case CHANGE_MAP_DIRECTION:
		return getChangeMapDirection(item, mapHeight);
		break;
	case AUTO_MOVE_VIEWPORT:
		return getAutoMoveViewport(item, mapHeight);
		break;
	case FIRE:
		return getFire(item, mapHeight);
		break;
	case BLUE_DOOR:
		return getBlueDoor(item, mapHeight);
		break;
	case RED_DOOR:
		return getRedDoor(item, mapHeight);
		break;
	case BREAKABLE_BLUE_WALL:
		return getBreakableBlueWall(item, mapHeight);
		break;
	case BREAKABLE_RED_WALL:
		return getBreakableRedWall(item, mapHeight);
		break;
	case BLUE_ITEM_BALL:
		return getBlueItemBall(item, mapHeight);
		break;
	case RED_ITEM_BALL:
		return getRedItemBall(item, mapHeight);
		break;
	case RIPPER:
		return getRipper(item, mapHeight);
		break;
	case WAVER:
		return getWaver(item, mapHeight);
		break;
	case SKREE:
		return getSkree(item, mapHeight);
		break;
	case MELLOW:
		return getMellow(item, mapHeight);
		break;
	case RIO:
		return getRio(item, mapHeight);
		break;
	case ZEB_PIPE:
		return getZebPipe(item, mapHeight);
		break;
	case ZOOMER:
		return getZoomer(item, mapHeight);
		break;
	case ZEEBETITE:
		return getZeebetite(item, mapHeight);
		break;
	case METROID:
		return getMetroid(item, mapHeight);
		break;
	case MOTHER_BRAIN:
		return getMotherBrain(item, mapHeight);
		break;
	case RINKA_CANNON:
		return getRinkaCannon(item, mapHeight);
		break;
	case LEFT_CANNON:
		return getLeftCannon(item, mapHeight);
		break;
	case MIDDLE_CANNON:
		return getMiddleCannon(item, mapHeight);
		break;
	case RIGHT_CANNON:
		return getRightCannon(item, mapHeight);
		break;
	case RIDLEY:
		return getRidley(item, mapHeight);
		break;
	case ENERGY_TANK:
		return getEnergyTank(item, mapHeight);
		break;
	case ENERGY_BALL:
		return getEnergyBall(item, mapHeight);
		break;
	case MARU_MARI:
		return getMaruMari(item, mapHeight);
		break;
	case LONG_BEAM:
		return getLongBeam(item, mapHeight);
		break;
	case ICE_BEAM:
		return getIceBeam(item, mapHeight);
		break;
	case MISSILE_ROCKET_BALL:
		return getMissileRocketBall(item, mapHeight);
		break;
	case BOMB_BALL:
		return getBombBall(item, mapHeight);
		break;
	case VARIA:
		return getVaria(item, mapHeight);
		break;
	default:
		return nullptr;
	}
}

BaseObject* getWall(xml_node item, int mapHeight)
{
	auto properties = getObjectProperties(item);
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

BaseObject* getChangeMapDirection(xml_node item, int mapHeight)
{
	auto properties = getObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	// Do tọa độ được tạo từ Tiled Map Editor là top-left, nên ta chuyển về tọa độ world (x, y)
	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	auto mapDirection = (eMapDirection)stoi(properties["direction"]);
	auto anchorPointX = 2 * stoi(properties["anchorpointx"]);
	auto anchorPointY = mapHeight - 2 * stoi(properties["anchorpointy"]) - height;
	auto mapDirectionAnchorPoint = GVector2(anchorPointX, anchorPointY);

	auto changeMapDirection = new ChangeMapDirection(x, y, width, height, mapDirection, mapDirectionAnchorPoint);
	changeMapDirection->init();
	return changeMapDirection;
}

BaseObject* getAutoMoveViewport(xml_node item, int mapHeight)
{
	auto properties = getObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	auto autoMoveViewport = new AutoMoveViewport(x, y, width, height);
	autoMoveViewport->init();
	return autoMoveViewport;
}

BaseObject* getFire(xml_node item, int mapHeight)
{
	auto properties = getObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	auto fire = new Fire(x, y, width, height);
	fire->init();
	return fire;
}

BaseObject* getBlueDoor(xml_node item, int mapHeight)
{
	auto properties = getObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 2;

	auto blueDoor = new BlueDoor(x, y);
	blueDoor->init();
	return blueDoor;
}

BaseObject* getRedDoor(xml_node item, int mapHeight)
{
	auto properties = getObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 2;

	auto redDoor = new RedDoor(x, y);
	redDoor->init();
	return redDoor;
}

BaseObject* getBreakableBlueWall(xml_node item, int mapHeight)
{
	auto properties = getObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 2;

	auto breakableBlueWall = new BreakableBlueWall(x, y);
	breakableBlueWall->init();
	return breakableBlueWall;
}

BaseObject* getBreakableRedWall(xml_node item, int mapHeight)
{
	auto properties = getObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 2;

	auto breakableRedWall = new BreakableRedWall(x, y);
	breakableRedWall->init();
	return breakableRedWall;
}

BaseObject* getBlueItemBall(xml_node item, int mapHeight)
{
	auto properties = getObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	auto itemId = (eID)stoi(properties["itemid"]);

	x = x + width / 2;
	y = y + height / 2;

	auto blueItemBall = new BlueItemBall(x, y, itemId);
	blueItemBall->init();
	return blueItemBall;
}

BaseObject* getRedItemBall(xml_node item, int mapHeight)
{
	auto properties = getObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	auto itemId = (eID)stoi(properties["itemid"]);

	x = x + width / 2;
	y = y + height / 2;

	auto redItemBall = new RedItemBall(x, y, itemId);
	redItemBall->init();
	return redItemBall;
}

BaseObject* getRipper(xml_node item, int mapHeight)
{
	auto properties = getObjectProperties(item);
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

BaseObject* getWaver(xml_node item, int mapHeight)
{
	auto properties = getObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 2;

	auto waver = new Waver(x, y, false);
	waver->init();
	return waver;
}

BaseObject* getSkree(xml_node item, int mapHeight)
{
	auto properties = getObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 2;

	auto skree = new Skree(x, y);
	skree->init();
	return skree;
}

BaseObject* getMellow(xml_node item, int mapHeight)
{
	auto properties = getObjectProperties(item);
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

BaseObject* getRio(xml_node item, int mapHeight)
{
	auto properties = getObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 2;

	auto rio = new Rio(x, y, false);
	rio->init();
	return rio;
}

BaseObject* getZebPipe(xml_node item, int mapHeight)
{
	auto properties = getObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	auto zebPipe = new ZebPipe(x, y, width, height);
	zebPipe->init();
	return zebPipe;
}

BaseObject* getZoomer(xml_node item, int mapHeight)
{
	auto properties = getObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 2;

	auto zoomer = new Zoomer(x, y);
	zoomer->init();
	return zoomer;
}

BaseObject* getZeebetite(xml_node item, int mapHeight)
{
	auto properties = getObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 2;

	auto zeebetite = new Zeebetite(x, y);
	zeebetite->init();
	return zeebetite;
}

BaseObject* getMetroid(xml_node item, int mapHeight)
{
	auto properties = getObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 2;

	auto metroid = new Metroid(x, y, false);
	metroid->init();
	return metroid;
}

BaseObject* getMotherBrain(xml_node item, int mapHeight)
{
	auto properties = getObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 2;

	auto motherBrain = new MotherBrain(x, y);
	motherBrain->init();
	return motherBrain;
}

BaseObject* getRinkaCannon(xml_node item, int mapHeight)
{
	auto properties = getObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	auto rinkaCannon = new RinkaCannon(x, y, width, height);
	rinkaCannon->init();
	return rinkaCannon;
}

BaseObject* getLeftCannon(xml_node item, int mapHeight)
{
	auto properties = getObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 2;

	auto leftCannon = new LeftCannon(x, y);
	leftCannon->init();
	return leftCannon;
}

BaseObject* getMiddleCannon(xml_node item, int mapHeight)
{
	auto properties = getObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 2;

	auto middleCannon = new MiddleCannon(x, y);
	middleCannon->init();
	return middleCannon;
}

BaseObject* getRightCannon(xml_node item, int mapHeight)
{
	auto properties = getObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 2;

	auto rightCannon = new RightCannon(x, y);
	rightCannon->init();
	return rightCannon;
}

BaseObject* getRidley(xml_node item, int mapHeight)
{
	auto properties = getObjectProperties(item);
	if (properties.size() == 0)
		return nullptr;

	auto width = 2 * stoi(properties["width"]);
	auto height = 2 * stoi(properties["height"]);
	auto x = 2 * stoi(properties["x"]);
	auto y = mapHeight - 2 * stoi(properties["y"]) - height;

	x = x + width / 2;
	y = y + height / 2;

	auto ridley = new Ridley(x, y);
	ridley->init();
	return ridley;
}

BaseObject* getEnergyTank(xml_node item, int mapHeight)
{
	auto properties = getObjectProperties(item);
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

BaseObject* getEnergyBall(xml_node item, int mapHeight)
{
	auto properties = getObjectProperties(item);
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

BaseObject* getMaruMari(xml_node item, int mapHeight)
{
	auto properties = getObjectProperties(item);
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

BaseObject* getLongBeam(xml_node item, int mapHeight)
{
	auto properties = getObjectProperties(item);
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

BaseObject* getIceBeam(xml_node item, int mapHeight)
{
	auto properties = getObjectProperties(item);
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

BaseObject* getMissileRocketBall(xml_node item, int mapHeight)
{
	auto properties = getObjectProperties(item);
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

BaseObject* getBombBall(xml_node item, int mapHeight)
{
	auto properties = getObjectProperties(item);
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

BaseObject* getVaria(xml_node item, int mapHeight)
{
	auto properties = getObjectProperties(item);
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
