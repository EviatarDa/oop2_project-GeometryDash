#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2D/Box2D.h>
#include "Resources.h"
#include "GameObject.h"

class MyContactListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact*) override;
};