#pragma once
#include "Gate.h"



Gate::Gate(b2World& world, const GameTextures texture, const sf::Vector2f location,
	const bool, const GameAnimations, const GameTextures)
	:StaticObject(world, texture, location)
{
}


//register all the gates to the static object factory
bool Gate::m_registerit1 = Factory<StaticObject>::registerObject(GATE1_COLOR,
	[](b2World& world, const sf::Vector2f location) -> std::unique_ptr<StaticObject>
	{
		return std::make_unique<Gate>(world, Gate1, location, false, (GameAnimations)0, (GameTextures)0);
	});

bool Gate::m_registerit2 = Factory<StaticObject>::registerObject(GATE2_COLOR,
	[](b2World& world, const sf::Vector2f location) -> std::unique_ptr<StaticObject>
	{
		return std::make_unique<Gate>(world, Gate2, location, false, (GameAnimations)0, (GameTextures)0);
	});

bool Gate::m_registerit3 = Factory<StaticObject>::registerObject(GATE3_COLOR,
	[](b2World& world, const sf::Vector2f location) -> std::unique_ptr<StaticObject>
	{
		return std::make_unique<Gate>(world, Gate3, location, false, (GameAnimations)0, (GameTextures)0);
	});

bool Gate::m_registerit4 = Factory<StaticObject>::registerObject(GATE4_COLOR,
	[](b2World& world, const sf::Vector2f location) -> std::unique_ptr<StaticObject>
	{
		return std::make_unique<Gate>(world, Gate4, location, false, (GameAnimations)0, (GameTextures)0);
	});

bool Gate::m_registerit5 = Factory<StaticObject>::registerObject(GATE5_COLOR,
	[](b2World& world, const sf::Vector2f location) -> std::unique_ptr<StaticObject>
	{
		return std::make_unique<Gate>(world, Gate5, location, false, (GameAnimations)0, (GameTextures)0);
	});
