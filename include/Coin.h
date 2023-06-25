#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2D/Box2D.h>
#include "Resources.h"
#include "StaticObject.h"
#include "Factory.h"


class Coin : public StaticObject
{
public:
	Coin(b2World& world, const GameTextures texture, const sf::Vector2f location,
		const bool , const GameAnimations , const GameTextures );

private:
	static bool m_registerit1;
};
