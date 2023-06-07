#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2D/Box2D.h>
#include "Resources.h"
#include "StaticObject.h"


class Coin : public StaticObject
{
public:
	Coin(GameTextures, sf::Vector2f);

private:

};
