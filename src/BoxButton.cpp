#pragma once

#include "BoxButton.h"
#include "Game.h"


BoxButton::BoxButton(Game* game)
	:Command(game)
{
}

void BoxButton::execute()
{
	m_game->chooseBoxShip();
}
