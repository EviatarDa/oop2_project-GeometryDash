#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Resources.h>

class Game;

class Command {
public:
	Command(Game*, sf::RenderWindow&);
	virtual void execute() = 0;
	virtual ~Command() = default;

protected:
	Game* m_game;
	sf::RenderWindow& m_window;
	
};