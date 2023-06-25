#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2D/Box2D.h>
#include "Resources.h"
#include "Board.h"
#include "Menu.h"
#include "ScoreTable.h"
#include "HelpButton.h"
#include "PlayButton.h"
#include "BoxButton.h"
#include "ScoreTableButton.h"


class Game
{
public:
	Game();
	void runMenu();
	void startGame();
	void chooseBoxShip();
	void handleBoxShipPageClick(const sf::Vector2f);
	void handleBoxShipMouseMoved(const sf::Vector2f);
	Board& getBoard();
	Menu& getMenu();

private:
	sf::RenderWindow m_window;
	Resources& m_resource = Resources::instance();
	Menu m_menu;
	Board m_board;
	sf::View m_gameView;
	bool m_game_over = false;
	sf::Clock m_game_clock;

	//private functions
	void setView();
	void winLoop();
	void createScoreBoard(sf::Sprite&, sf::Sprite&, sf::Text&, sf::Text&, int&,
		sf::Text&, sf::Text&, sf::RectangleShape&, sf::RectangleShape&);

};