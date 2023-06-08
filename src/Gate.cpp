#include "Gate.h"
#pragma once

#include "Gate.h"

Gate::Gate(b2World& world, GameTextures texture, sf::Vector2f location)
	:StaticObject(world, texture, location),
	m_type(texture)
{
}

GameTextures Gate::getType()
{
	return m_type;
}
