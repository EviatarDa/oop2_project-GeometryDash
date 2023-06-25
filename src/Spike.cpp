#pragma once

#include "Spike.h"


Spike::Spike(b2World& world, const GameTextures texture, const sf::Vector2f location , const bool up,
	const GameAnimations, const GameTextures)
	:StaticObject(world, texture, location)
{
	if (up)
	{
		m_object.rotate(180);
	}
}



bool Spike::m_registerit1 = Factory<StaticObject>::registerObject(SPIKE1_COLOR,
	[](b2World& world, const sf::Vector2f location) -> std::unique_ptr<StaticObject> {
		return std::make_unique<Spike>(world, Spike1, location, false, (GameAnimations)0, (GameTextures)0); }
);

bool Spike::m_registerit2 = Factory<StaticObject>::registerObject(SPIKE2_COLOR,
	[](b2World& world, const sf::Vector2f location) -> std::unique_ptr<StaticObject> {
		return std::make_unique<Spike>(world, Spike2,
		sf::Vector2f(location.x, location.y + 13), false, (GameAnimations)0, (GameTextures)0); }
);

bool Spike::m_registerit3 = Factory<StaticObject>::registerObject(SPIKE1_UP_COLOR,
	[](b2World& world, const sf::Vector2f location) -> std::unique_ptr<StaticObject> {
		return std::make_unique<Spike>(world, Spike1, location, true, (GameAnimations)0, (GameTextures)0); }
);

bool Spike::m_registerit4 = Factory<StaticObject>::registerObject(SPIKES_COLOR,
	[](b2World& world, const sf::Vector2f location) -> std::unique_ptr<StaticObject> {
		return std::make_unique<Spike>(world, Spikes, location,false, (GameAnimations)0, (GameTextures)0); }
);