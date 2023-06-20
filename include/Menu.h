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

	std::pair<GameTextures, GameTextures> getPlayerTextures();
	void chooseBoxShip(MenuBoxShips);

	void drawLevelsPage();

	void updateScoreTable(int, std::string);

	void playSong();
	void stopSong();

private:

	sf::RenderWindow& m_window;
	sf::Sprite m_background;
	sf::Sprite m_title;
	ScoreTable m_score_table;


	sf::Sprite m_buttons[MENU_BUTTONS];
	sf::Sprite m_back_buttons[MENU_BUTTONS];
	sf::Sprite m_instructions[MENU_INSTRUCTIONS];
	sf::Sprite m_box_ships[MENU_BOX_SHIPS];
	sf::RectangleShape m_box_ships_rect[MENU_BOX_SHIPS];
	sf::Text m_box_ship_text;
	MenuBoxShips m_box_ship;
	sf::Sound m_menu_sound;

	void locateObjects();

};
