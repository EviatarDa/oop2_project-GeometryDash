#pragma once
#include "Factory.h"



//bool Factory::registerStaticObject(sf::Color object, pFncStatic fnc)
//{
//    //Insert the object to the map (color, function)
//	Factory::getMapStatic().emplace(object, fnc);
//	return true;
//}
//
//bool Factory::registerMovingObject(sf::Color object, pFncMove fnc)
//{
//    //Insert the object to the map (color, function)
//	Factory::getMapMoving().emplace(object, fnc);
//	return true;
//}
//
//
//
//std::unique_ptr<StaticObject> Factory::createStatic(sf::Color object_color, b2World& world, sf::Vector2f location) {
//	auto it = Factory::getMapStatic().find(object_color);
//	if (it == Factory::getMapStatic().end())
//		return nullptr;
//    //Call the function lambda - return a static object
//	return it->second(world,location);
//}
//
//std::unique_ptr<MovingObject> Factory::createMoving(sf::Color object_color, b2World& world, sf::Vector2f location) {
//	auto it = Factory::getMapMoving().find(object_color);
//	if (it == Factory::getMapMoving().end())
//		return nullptr;
//    //Call the function lambda - return a moving object
//	return it->second(world, location);
//}
//
//
//bool Factory::isExistMove(sf::Color color) {
//    const auto& mapMoving = getMapMoving();
//    
//
//    // Check in the map of MovingObjects
//    for (const auto& pair : mapMoving) {
//        if (pair.first == color) {
//            return true;
//        }
//    }
//    return false;
//}
//
//
//bool Factory::isExistStatic(sf::Color color) {
//
//    const auto& mapStatic = getMapStatic();
//
//    // Check in the map of StaticObjects
//    for (const auto& pair : mapStatic) {
//        if (pair.first == color) {
//            return true;
//        }
//    }
//
//    return false;
//}
