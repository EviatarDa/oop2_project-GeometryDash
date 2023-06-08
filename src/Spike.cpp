#pragma once

#include "Spike.h"

Spike::Spike(b2World& world, GameTextures texture, sf::Vector2f location)
	:StaticObject(world, texture, location)
{
}
