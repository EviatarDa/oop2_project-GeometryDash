#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2D/Box2D.h>
#include "Resources.h"
#include "StaticObject.h"


class Spike : public StaticObject
{
public:
	Spike(b2World&, GameTextures, sf::Vector2f, bool);

private:

};