#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Resources.h>
#include "Command.h"

class LevelsMenu
{
public:
	LevelsMenu(Game*, sf::RenderWindow&);
	void drawLevelsMenu()const;
	int getOptionFromUser(sf::Vector2f);
	void performAction(int);
	void add(LevelsMenuButtons, std::unique_ptr<Command>);
	void handleLevelMenuMouseMoved(sf::Vector2f);
	void ButtonPress(const LevelsMenuButtons);
	void ButtonRelease(const LevelsMenuButtons);

private:

	sf::RenderWindow& m_window;
	Game* m_game;
	sf::Sprite m_background;
	sf::Sprite m_buttons[MENU_BUTTONS];
	sf::Sprite m_back_buttons[MENU_BUTTONS];

	typedef std::pair<sf::Sprite, std::unique_ptr<Command>> option;
	std::vector<option> m_options;

	void locateObjects();

};
