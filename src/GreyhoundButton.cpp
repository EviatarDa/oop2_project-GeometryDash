#pragma once

#include "GreyhoundButton.h"
#include "Game.h"

GreyhoundButton::GreyhoundButton(Game* game)
	:Command(game)
{
}

void GreyhoundButton::execute()
{
	m_game->getMenu().stopSong();
	m_game->getBoard().createLevel(Map2, Greyhound_Song);
	m_game->startGame();
	m_game->getMenu().playSong();
}
