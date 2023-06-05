#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2D/Box2D.h>
#include "Resources.h"

class MovingObject
{
public:
	MovingObject(b2World&, GameTextures);
	virtual ~MovingObject();
	void draw(sf::RenderWindow&);
	b2Vec2 getPosition();
	virtual void updateDirection() = 0;
	virtual void move() = 0;

	b2Body* getBody()const;

protected:
	//b2World& m_world;
	sf::Sprite m_object;
	b2Body* m_object_body;

};