#include "Gate.h"
#pragma once

#include "Gate.h"

Gate::Gate(b2World& world, GameTextures texture, sf::Vector2f location)
	:StaticObject(world, texture, location)
{
}

//bool Gate::isActive()
//{
//	return m_active;
//}
//
//void Gate::shutDown()
//{
//	m_active = false;
//}

