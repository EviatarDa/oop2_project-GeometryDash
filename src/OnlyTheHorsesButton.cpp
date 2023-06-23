#pragma once

#include "OnlyTheHorsesButton.h"
#include "Game.h"

OnlyTheHorsesButton::OnlyTheHorsesButton(Game* game)
	:Command(game)
{
}

void OnlyTheHorsesButton::execute()
{
	m_game->getMenu().stopSong();
	m_game->getBoard().createLevel(Map3, OnlyTheHorses_Song	);
	m_game->startGame();
	m_game->getMenu().playSong();
}
