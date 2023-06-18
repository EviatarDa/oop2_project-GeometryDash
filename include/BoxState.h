#pragma once

#include "PlayerState.h"

class BoxState : public PlayerState
{
public:
	void move(bool*, b2Body*, bool&, b2Vec2, sf::Sprite&)override;
	void collideBrick(bool&, bool&)override;

private:
};