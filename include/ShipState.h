#pragma once

#include "PlayerState.h"

class ShipState : public PlayerState
{
public:
	void move(Direction, b2Body*) override;

private:
};