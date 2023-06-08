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
	b2Vec2 getPosition();
	virtual void updateDirection() = 0;
	virtual void move() = 0;

	void setDead();
	bool isAlive();
	virtual void kill() = 0;

protected:
	bool m_alive = true;

};