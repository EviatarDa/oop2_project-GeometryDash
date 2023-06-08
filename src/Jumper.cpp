#pragma once

#include "Jumper.h"

Jumper::Jumper(b2World& world, GameTextures texture, sf::Vector2f location)
	:StaticObject(world, texture, location)
{
}
