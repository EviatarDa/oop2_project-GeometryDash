#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Resources.h>
#include "ScoreTable.h"

class Menu
{
public:
	Menu(sf::RenderWindow&);
	void drawMenu()const;
	sf::Sprite getButton(const MenuButtons) const;
	void ButtonPress(const MenuButtons);
	void ButtonRelease(const MenuButtons);

	sf::Sprite getBoxShip(const MenuBoxShips) const;
	void boxShipPress(const MenuBoxShips);
	void boxShipRelease(const MenuBoxShips);

	void drawInstructions(const MenuInstructions) const;
	void drawScoreTable();
	void drawBoxShips();


private:

	sf::RenderWindow& m_window;
	sf::Sprite m_background;
	sf::Sprite m_title;
	sf::Sprite m_Authors;

	ScoreTable m_score_teble;

	sf::Sprite m_buttons[MENU_BUTTONS];
	sf::Sprite m_back_buttons[MENU_BUTTONS];
	sf::Sprite m_instructions[MENU_INSTRUCTIONS];
	sf::Sprite m_box_ships[MENU_BOX_SHIPS];
	sf::RectangleShape m_box_ships_rect[MENU_BOX_SHIPS];

	void locateObjects();

};
