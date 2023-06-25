#include "Coin.h"

#pragma once



Coin::Coin(b2World& world, const GameTextures texture, const sf::Vector2f location,
	const bool , const GameAnimations , const GameTextures )
	:StaticObject(world, texture, location)
{
}

bool Coin::m_registerit1 = Factory<StaticObject>::registerObject(COIN_COLOR,
	[](b2World& world, sf::Vector2f location) -> std::unique_ptr<StaticObject> {
		return std::make_unique<class Coin>(world, GameTextures::Coin, location,
		false, (GameAnimations)0, (GameTextures)0); }
);