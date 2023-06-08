#include "Coin.h"
#include "Coin.h"
#pragma once

#include "Coin.h"

Coin::Coin(b2World& world, GameTextures texture, sf::Vector2f location)
	:StaticObject(world, texture, location),
	m_delete(false)
{
}

void Coin::setDelete()
{
	m_delete = true;
}

bool Coin::getDelete()
{
	return m_delete;
}
