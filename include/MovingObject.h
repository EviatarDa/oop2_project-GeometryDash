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
	virtual void updateDirection() = 0;
	virtual void move() = 0;


	//void setDead();//
	//bool isAlive();//
	//virtual void kill() {};//
	//virtual void handleMarking() {};//

	//void setGravity();//
	//bool isGravityMarked();//

	//virtual bool isBoxStateMarked() { return false; };//
	//virtual void handleBoxStateMarking() {};//

	//virtual bool isShipStateMarked() { return false;};//
	//virtual void handleShipStateMarking() {};//
	//
	//virtual bool isWinner() { return false; };//

protected:




};