#pragma once

#include "PlayerState.h"

class ShipState : public PlayerState
{
public:
	void move(bool*, b2Body*, bool&) override;

private:
};