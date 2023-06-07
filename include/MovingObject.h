#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2D/Box2D.h>
#include "Resources.h"
#include "GameObject.h"


class MovingObject : public GameObject
{
public:
	MovingObject(b2World&, GameTextures, sf::Vector2f);
	//virtual ~MovingObject();
	//void draw(sf::RenderWindow&);
	b2Vec2 getPosition();
	virtual void updateDirection() = 0;
	virtual void move() = 0;

	//b2Body* getBody()const;

//protected:
	//sf::Sprite m_object;
	//b2Body* m_object_body;

};