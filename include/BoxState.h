#pragma once

#include "PlayerState.h"

class BoxState : public PlayerState
{
public:
	void move(bool*, b2Body*, bool&)override;
	void collideBrick(bool&, bool&)override;

private:
};