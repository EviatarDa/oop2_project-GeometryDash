#pragma once

#include "Brick.h"


Brick::Brick(b2World& world, GameTextures texture, sf::Vector2f location,
	bool, GameAnimations, GameTextures)
	:StaticObject(world, texture, location)
{
}


bool Brick::m_registerit1 = Factory::registerStaticObject(CUBE1_COLOR,
	[](b2World& world, sf::Vector2f location) -> std::unique_ptr<StaticObject> {
		return std::make_unique<Brick>(world, Cube1, location, false, (GameAnimations)0, (GameTextures)0); });

bool Brick::m_registerit2 = Factory::registerStaticObject(CUBE2_COLOR,
	[](b2World& world, sf::Vector2f location) -> std::unique_ptr<StaticObject> {
		return std::make_unique<Brick>(world, Cube2, location, false, (GameAnimations)0, (GameTextures)0); });

bool Brick::m_registerit3 = Factory::registerStaticObject(CUBE_CUBE_COLOR,
	[](b2World& world, sf::Vector2f location) -> std::unique_ptr<StaticObject> {
		return std::make_unique<Brick>(world, CubeCube, location, false, (GameAnimations)0, (GameTextures)0); });

bool Brick::m_registerit4 = Factory::registerStaticObject(FLOOR_COLOR,
	[](b2World& world, sf::Vector2f location) -> std::unique_ptr<StaticObject> {
		return std::make_unique<Brick>(world, Floor, location, false, (GameAnimations)0, (GameTextures)0); });

bool Brick::m_registerit5 = Factory::registerStaticObject(RECTANGLE_COLOR,
	[](b2World& world, sf::Vector2f location) -> std::unique_ptr<StaticObject> {
		return std::make_unique<Brick>(world, Rectangle, sf::Vector2f(location.x,location.y+13), false,
		(GameAnimations)0, (GameTextures)0); });