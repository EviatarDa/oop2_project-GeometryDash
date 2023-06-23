#pragma once

#include "HelpButton.h"
#include "Game.h"

HelpButton::HelpButton(Game* game)
	:Command(game)
{
}

void HelpButton::execute()
{
	m_game->instructions();
}
