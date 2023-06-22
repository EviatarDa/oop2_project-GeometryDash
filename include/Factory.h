#pragma once

#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include <string>
#include  "StaticObject.h"
#include  "MovingObject.h"
#include <SFML/Graphics.hpp>


struct ColorComparator {
	bool operator()(const sf::Color& color1, const sf::Color& color2) const {
		// Custom comparison logic based on RGB values with SFML Color class
		 return color1.toInteger() < color2.toInteger() ;
	}
};

template<class ObjectType>
class Factory {

public:

	//using pFncMove = std::unique_ptr<MovingObject>(*)(b2World& world, sf::Vector2f location);
	//using pFncStatic = std::unique_ptr<StaticObject>(*)(b2World& world, sf::Vector2f location);

	using p2Fnc = std::unique_ptr<ObjectType>(*)(b2World& world, sf::Vector2f location);


	//static std::unique_ptr<MovingObject> createMoving(sf::Color color,b2World& world,sf::Vector2f location);
	//static std::unique_ptr<StaticObject> createStatic(sf::Color color, b2World& world, sf::Vector2f location);

	static std::unique_ptr<ObjectType> createObject(sf::Color color, b2World& world, sf::Vector2f location);


	//static bool registerMovingObject(sf::Color, pFncMove);
	//static bool registerStaticObject(sf::Color, pFncStatic);

	static bool registerObject(sf::Color, p2Fnc);


	//static bool isExistMove(sf::Color color);
	//static bool isExistStatic(sf::Color color);


	static bool isExist(sf::Color color);


private:

	//static auto& getMapMoving() {
	//	static std::map<sf::Color, pFncMove, ColorComparator> mapMoving;
	//	return mapMoving;
	//}

	//static auto& getMapStatic() {
	//	static std::map<sf::Color, pFncStatic, ColorComparator> mapStatic;
	//	return mapStatic;
	//}

		static auto& getMap() {
		static std::map<sf::Color, p2Fnc, ColorComparator> map;
		return map;
	}
};

template<class ObjectType>
inline std::unique_ptr<ObjectType> Factory<ObjectType>::createObject(sf::Color object_color, b2World& world, sf::Vector2f location)
{
	auto it = Factory::getMap().find(object_color);
	if (it == Factory::getMap().end())
		return nullptr;
	//Call the function lambda - return a static object
	return it->second(world, location);
}

template<class ObjectType>
inline bool Factory<ObjectType>::registerObject(sf::Color object, p2Fnc fnc)
{
	//Insert the object to the map (color, function)
	Factory::getMap().emplace(object, fnc);
	return true;
}

template<class ObjectType>
inline bool Factory<ObjectType>::isExist(sf::Color color)
{
	const auto& map = getMap();

    // Check in the map of StaticObjects
    for (const auto& pair : map) {
        if (pair.first == color) {
            return true;
        }
    }
    return false;
}
