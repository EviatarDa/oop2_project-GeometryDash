#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Resources.h>
#include "ScoreTable.h"

#include "Command.h"

class Menu
{
public:
	Menu(sf::RenderWindow&);
	void drawMenu()const;
	void drawInstructions(const MenuInstructions) const;
	void drawScoreTable();
	void drawBoxShips();
	void drawLevelsPage();

	int getOptionFromUser(sf::Vector2f);
	void performAction(int);
	void add(MenuButtons, std::unique_ptr<Command>);

	void handleMenuMouseMoved(sf::Vector2f);
	void ButtonPress(const MenuButtons);
	void ButtonRelease(const MenuButtons);

	sf::Sprite getBoxShip(const MenuBoxShips) const;
	void boxShipPress(const MenuBoxShips);
	void boxShipRelease(const MenuBoxShips);



	std::pair<GameTextures, GameTextures> getPlayerTextures();
	void chooseBoxShip(MenuBoxShips);


	void updateScoreTable(int, std::string);

	void playSong();
	void stopSong();

	//sf::Sprite getButton(const MenuButtons) const;


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

	//from here
	typedef std::pair<sf::Sprite, std::unique_ptr<Command>> option;
	std::vector<option> m_options;
};
