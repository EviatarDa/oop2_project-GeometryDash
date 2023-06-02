#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2D/Box2D.h>
#include "Resources.h"

class MovingObject
{
public:
	MovingObject(b2World&, GameTextures);
	void draw(sf::RenderWindow&);
	b2Vec2 getPosition();
	virtual void updateDirection() = 0;
	virtual void move() = 0;

protected:
	sf::Sprite m_object;
	b2Body* m_object_body;

};