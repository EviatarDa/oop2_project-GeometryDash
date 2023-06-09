#pragma once

#include "PlayerState.h"

class BoxState : public PlayerState
{
public:
	void move(bool*, b2Body*, bool&)override;

private:
};