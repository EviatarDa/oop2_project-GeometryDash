#pragma once

#include "PlayerState.h"

class BoxState : public PlayerState
{
public:
	void move(Direction, b2Body*)override;

private:
};