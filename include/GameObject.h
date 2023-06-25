#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2D/Box2D.h>
#include "Resources.h"

class GameObject
{
public:
	GameObject(const GameTextures, const sf::Vector2f);
	virtual ~GameObject();
	void draw(sf::RenderWindow&) const;
	const b2Body* getBody()const;

protected:
	sf::Sprite m_object;
	b2Body* m_object_body;
	sf::Clock m_clock;

	
};