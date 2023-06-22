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


class Factory {

public:

	using pFncMove = std::unique_ptr<MovingObject>(*)(b2World& world, sf::Vector2f location);
	using pFncStatic = std::unique_ptr<StaticObject>(*)(b2World& world, sf::Vector2f location);


	static std::unique_ptr<MovingObject> createMoving(sf::Color color,b2World& world,sf::Vector2f location);
	static std::unique_ptr<StaticObject> createStatic(sf::Color color, b2World& world, sf::Vector2f location);


	static bool registerMovingObject(sf::Color, pFncMove);
	static bool registerStaticObject(sf::Color, pFncStatic);

	static bool isExistMove(sf::Color color);
	static bool isExistStatic(sf::Color color);
	

private:

	static auto& getMapMoving() {
		static std::map<sf::Color, pFncMove, ColorComparator> mapMoving;
		return mapMoving;
	}

	static auto& getMapStatic() {
		static std::map<sf::Color, pFncStatic, ColorComparator> mapStatic;
		return mapStatic;
	}


};

