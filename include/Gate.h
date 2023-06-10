#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2D/Box2D.h>
#include "Resources.h"
#include "StaticObject.h"


class Gate : public StaticObject
{
public:
	Gate(b2World&, GameTextures, sf::Vector2f);

private:

};