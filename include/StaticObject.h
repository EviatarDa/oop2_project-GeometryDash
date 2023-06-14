#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2D/Box2D.h>
#include "Resources.h"
#include "GameObject.h"

class StaticObject : public GameObject
{
public:
	StaticObject(b2World&, GameTextures, sf::Vector2f);
	//StaticObject(GameTextures, sf::Vector2f); //TODELETE
	virtual ~StaticObject();
	GameTextures getType();

	void setDelete();
	bool getDelete();

	bool isActive();
	void inactive();
	void shutDown();
	void restart();

protected:
	bool m_delete = false;
	bool m_active = true;
	bool m_fixture_destroyed = false;
	GameTextures m_type;
	sf::Time m_inactive_timer;

};