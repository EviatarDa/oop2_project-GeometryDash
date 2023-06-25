#pragma once

#include "WithoutYouButton.h"
#include "Game.h"

WithoutYouButton::WithoutYouButton(Game* game, sf::RenderWindow& window)
	:Command(game, window)
{
}

void WithoutYouButton::execute()
{
	m_game->getMenu().stopSong();
	m_game->getBoard().createLevel(Map1, WithoutYou_Song);
	m_game->startGame();
	m_game->getMenu().playSong();
}
