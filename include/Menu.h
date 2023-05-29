#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Resources.h>

class Menu
{
public:
	Menu();
	void drawMenu(sf::RenderWindow&)const;




private:
	sf::Sprite m_backgroung;
	sf::Sprite m_title;
	sf::Sprite m_Authors;

	sf::Sprite m_buttons[MENU_BUTTONS];
	sf::Sprite m_back_buttons[MENU_BUTTONS];

	void locateObjects();

};
