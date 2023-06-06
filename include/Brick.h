#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2D/Box2D.h>
#include "Resources.h"
#include "StaticObject.h"


class Brick : public StaticObject
{
public:
	Brick(b2World&, GameTextures, sf::Vector2f);

private:

};
