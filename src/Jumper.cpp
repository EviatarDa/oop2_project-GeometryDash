#pragma once

#include "Jumper.h"

Jumper::Jumper(b2World& world, GameTextures texture, sf::Vector2f location, bool up)
	:StaticObject(world, texture, location)
{
	if (up)
	{
		m_object.rotate(180);
	}
}
