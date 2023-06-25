#pragma once

#include "SpectreButton.h"
#include "Game.h"

SpectreButton::SpectreButton(Game* game, sf::RenderWindow& window)
	:Command(game, window)
{
}

void SpectreButton::execute() 
{
	m_game->getMenu().stopSong();
	m_game->getBoard().createLevel(Map4, Spectre_Song);
	m_game->startGame();
	m_game->getMenu().playSong();
}
