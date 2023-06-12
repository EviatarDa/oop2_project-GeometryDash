#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2D/Box2D.h>
#include "Resources.h"
#include "GameObject.h"
#include "MovingObject.h"
#include "StaticObject.h"
#include "Player.h"
#include "Brick.h"
#include "Coin.h"
#include "Gate.h"
#include "Spike.h"
#include "Jumper.h"
#include "Enemy.h"


#include <functional>
//#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>

class MyContactListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact*) override;
};