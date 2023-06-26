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
	void drawScoreTable()const;
	void drawBoxShips()const;

	const int getOptionFromUser(const sf::Vector2f)const;
	void performAction(const int)const;
	void add(const MenuButtons, std::unique_ptr<Command>);

	void handleMenuMouseMoved(const sf::Vector2f);
	void ButtonPress(const MenuButtons);
	void ButtonRelease(const MenuButtons);

	const sf::Sprite getBoxShip(const MenuBoxShips) const;
	void boxShipPress(const MenuBoxShips);
	void boxShipRelease(const MenuBoxShips);

	const std::pair<GameTextures, GameTextures> getPlayerTextures() const;
	void chooseBoxShip(const MenuBoxShips);

	void updateScoreTable(const int, std::string);

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

	typedef std::pair<const sf::Sprite, std::unique_ptr<Command>> option;
	std::vector<option> m_options;
};
