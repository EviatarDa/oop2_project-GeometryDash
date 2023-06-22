#pragma once
#include "Gate.h"



Gate::Gate(b2World& world, GameTextures texture, sf::Vector2f location,
	bool, GameAnimations, GameTextures)
	:StaticObject(world, texture, location)
{
}

bool Gate::m_registerit1 = Factory::registerStaticObject(GATE1_COLOR,
	[](b2World& world, sf::Vector2f location) -> std::unique_ptr<StaticObject>
	{
		return std::make_unique<Gate>(world, Gate1, location, false, (GameAnimations)0, (GameTextures)0);
	});


bool Gate::m_registerit2 = Factory::registerStaticObject(GATE2_COLOR,
	[](b2World& world, sf::Vector2f location) -> std::unique_ptr<StaticObject>
	{
		return std::make_unique<Gate>(world, Gate2, location, false, (GameAnimations)0, (GameTextures)0);
	});

bool Gate::m_registerit3 = Factory::registerStaticObject(GATE3_COLOR,
	[](b2World& world, sf::Vector2f location) -> std::unique_ptr<StaticObject>
	{
		return std::make_unique<Gate>(world, Gate3, location, false, (GameAnimations)0, (GameTextures)0);
	});

bool Gate::m_registerit4 = Factory::registerStaticObject(GATE4_COLOR,
	[](b2World& world, sf::Vector2f location) -> std::unique_ptr<StaticObject>
	{
		return std::make_unique<Gate>(world, Gate4, location, false, (GameAnimations)0, (GameTextures)0);
	});

bool Gate::m_registerit5 = Factory::registerStaticObject(GATE5_COLOR,
	[](b2World& world, sf::Vector2f location) -> std::unique_ptr<StaticObject>
	{
		return std::make_unique<Gate>(world, Gate5, location, false, (GameAnimations)0, (GameTextures)0);
	});
