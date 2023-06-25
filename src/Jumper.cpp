#pragma once

#include "Jumper.h"

Jumper::Jumper(b2World& world, const GameTextures texture, const sf::Vector2f location, const bool up,
	const GameAnimations, const GameTextures)
	:StaticObject(world, texture, location)
{
	if (up)
	{
		m_object.rotate(180);
	}
}


 bool Jumper::m_registerit1 = Factory<StaticObject>::registerObject(JUMPER1_COLOR,
	[](b2World& world, const sf::Vector2f location) -> std::unique_ptr<StaticObject> {
		return std::make_unique<Jumper>(world, Jumper1, sf::Vector2f(location.x, location.y + 13)
			, false, (GameAnimations)0, (GameTextures)0); }
);

 bool Jumper::m_registerit2 = Factory<StaticObject>::registerObject(JUMPER1_UP_COLOR,
	[](b2World& world, const sf::Vector2f location) -> std::unique_ptr<StaticObject> {
		return std::make_unique<Jumper>(world, Jumper1, sf::Vector2f(location.x, location.y - 12),
		true, (GameAnimations)0, (GameTextures)0); }
);

 bool Jumper::m_registerit3 = Factory<StaticObject>::registerObject(JUMPER2_COLOR,
	[](b2World& world, const sf::Vector2f location) -> std::unique_ptr<StaticObject> {
		return std::make_unique<Jumper>(world, Jumper2, location, false, (GameAnimations)0, (GameTextures)0); }
);