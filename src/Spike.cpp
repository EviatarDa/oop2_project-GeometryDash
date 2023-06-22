#pragma once

#include "Spike.h"


Spike::Spike(b2World& world, GameTextures texture, sf::Vector2f location ,bool up,
	GameAnimations, GameTextures)
	:StaticObject(world, texture, location)
{
	if (up)
	{
		m_object.rotate(180);
	}
}



bool Spike::m_registerit1 = Factory::registerStaticObject(SPIKE1_COLOR,
	[](b2World& world, sf::Vector2f location) -> std::unique_ptr<StaticObject> {
		return std::make_unique<Spike>(world, Spike1, location, false, (GameAnimations)0, (GameTextures)0); }
);

bool Spike::m_registerit2 = Factory::registerStaticObject(SPIKE2_COLOR,
	[](b2World& world, sf::Vector2f location) -> std::unique_ptr<StaticObject> {
		return std::make_unique<Spike>(world, Spike2,
		sf::Vector2f(location.x, location.y + 13), false, (GameAnimations)0, (GameTextures)0); }
);

bool Spike::m_registerit3 = Factory::registerStaticObject(SPIKE1_UP_COLOR,
	[](b2World& world, sf::Vector2f location) -> std::unique_ptr<StaticObject> {
		return std::make_unique<Spike>(world, Spike1, location, true, (GameAnimations)0, (GameTextures)0); }
);

bool Spike::m_registerit4 = Factory::registerStaticObject(SPIKES_COLOR,
	[](b2World& world, sf::Vector2f location) -> std::unique_ptr<StaticObject> {
		return std::make_unique<Spike>(world, Spikes, location,false, (GameAnimations)0, (GameTextures)0); }
);