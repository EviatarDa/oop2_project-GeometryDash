#pragma once

#include "Brick.h"

Brick::Brick(b2World& world, GameTextures texture, sf::Vector2f location)
	:StaticObject(world, texture, location)
{
}
