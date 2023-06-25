#pragma once 

#include "Command.h"

Command::Command( Game* game, sf::RenderWindow& window)
	:m_game(game), m_window(window)
{
}
