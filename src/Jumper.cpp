#pragma once

#include "Jumper.h"

Jumper::Jumper(b2World& world, GameTextures texture, sf::Vector2f location, bool up,
	GameAnimations, GameTextures)
	:StaticObject(world, texture, location)
{
	if (up)
	{
		m_object.rotate(180);
	}
}


 bool Jumper::m_registerit1 = Factory::registerStaticObject(JUMPER1_COLOR,
	[](b2World& world, sf::Vector2f location) -> std::unique_ptr<StaticObject> {
		return std::make_unique<Jumper>(world, Jumper1, sf::Vector2f(location.x, location.y + 13)
			, false, (GameAnimations)0, (GameTextures)0); }
);

 bool Jumper::m_registerit2 = Factory::registerStaticObject(JUMPER1_UP_COLOR,
	[](b2World& world, sf::Vector2f location) -> std::unique_ptr<StaticObject> {
		return std::make_unique<Jumper>(world, Jumper1, sf::Vector2f(location.x, location.y - 12),
		true, (GameAnimations)0, (GameTextures)0); }
);

 bool Jumper::m_registerit3 = Factory::registerStaticObject(JUMPER2_COLOR,
	[](b2World& world, sf::Vector2f location) -> std::unique_ptr<StaticObject> {
		return std::make_unique<Jumper>(world, Jumper2, location, false, (GameAnimations)0, (GameTextures)0); }
);