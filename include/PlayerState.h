#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2D/Box2D.h>
#include "Resources.h"

class PlayerState
{
public:
    virtual ~PlayerState() = default;
    virtual void move(Direction, b2Body*) = 0;

private:
};
