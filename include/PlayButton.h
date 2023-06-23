#pragma once

#include "Command.h"
#include "LevelsMenu.h"

class Game;

class PlayButton : public Command 
{
public:
	PlayButton(Game*, sf::RenderWindow&);
	virtual void execute() override;

private:
	sf::RenderWindow& m_window;
	LevelsMenu m_levels_menu;
};
