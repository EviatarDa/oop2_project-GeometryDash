#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2D/Box2D.h>
#include "Resources.h"
#include "StaticObject.h"
#include "Factory.h"


class Gate : public StaticObject
{
public:
	Gate(b2World& world, const GameTextures texture, const sf::Vector2f location,
		const bool, const GameAnimations, const GameTextures);

private:
	static bool m_registerit1;
	static bool m_registerit2;
	static bool m_registerit3;
	static bool m_registerit4;
	static bool m_registerit5;
};