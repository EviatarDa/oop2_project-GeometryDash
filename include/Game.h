#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2D/Box2D.h>
#include "Resources.h"
#include "Board.h"
#include "Menu.h"
#include "ScoreTable.h"


class Game
{
public:
	Game();
	void runMenu();

private:
	sf::RenderWindow m_window;
	Resources& m_resource = Resources::instance();
	Menu m_menu;
	Board m_board;
	sf::View m_gameView;
	bool m_game_over = false;
	sf::Clock m_game_clock;

	//functions
	void handleMenuMouseMoved(const sf::Vector2f, int , int);
	void handleBoxShipMouseMoved(const sf::Vector2f);
	void handleMenuClick(const sf::Vector2f);
	void handleBoxShipPageClick(const sf::Vector2f);
	void handleLevelsPageClick(const sf::Vector2f);
	void startGame();
	void setView();
	void instructions();
	void scoreTable();
	void chooseBoxShip();
	void chooseLevel();
	void winLoop();
	void createScoreBoard(sf::Sprite&, sf::Sprite&, sf::Text&, sf::Text&, int&);

};