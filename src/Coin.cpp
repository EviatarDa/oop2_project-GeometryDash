#include "Coin.h"

#pragma once



Coin::Coin(b2World& world, GameTextures texture, sf::Vector2f location,
	bool , GameAnimations , GameTextures )

	:StaticObject(world, texture, location)
{
}

bool Coin::m_registerit1 = Factory::registerStaticObject(COIN_COLOR,
	[](b2World& world, sf::Vector2f location) -> std::unique_ptr<StaticObject> {
		return std::make_unique<class Coin>(world, GameTextures::Coin, location,
		false, (GameAnimations)0, (GameTextures)0); }
);