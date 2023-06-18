#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2D/Box2D.h>
#include "Resources.h"
#include "GameObject.h"
//#include <limits>


class MovingObject : public GameObject
{
public:
	MovingObject(b2World&, GameTextures, sf::Vector2f);
	b2Vec2 getPosition();
	virtual void updateDirection() {};
	virtual void move() = 0;
	virtual void releaseRight() {};
	virtual void releaseLeft() {};
	virtual void releaseSpace() {};

	void setDead();
	bool isAlive();
	virtual void kill() {};

	//void setState();
	//bool isStateMarked();
	virtual void handleMarking() {};

	void setGravity();
	bool isGravityMarked();

	//TOCHECK
	//virtual void setBoxState() {};
	virtual bool isBoxStateMarked() { return false; };
	virtual void handleBoxStateMarking() {};

	//virtual void setShipState() {};
	virtual bool isShipStateMarked() { return false;};
	virtual void handleShipStateMarking() {};
	
	virtual bool isWinner() { return false; };

protected:
	bool m_alive = true;
	bool m_state_change = false;
	bool m_gravity_changed = false;



};