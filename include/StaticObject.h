#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2D/Box2D.h>
#include "Resources.h"
#include "GameObject.h"

class StaticObject : public GameObject
{
public:
	StaticObject(b2World&, GameTextures, sf::Vector2f);
	StaticObject(GameTextures, sf::Vector2f); //TODELETE
	virtual bool getDelete();
};