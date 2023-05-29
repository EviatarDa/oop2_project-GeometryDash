#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Box2D/Box2D.h>
#include "Resources.h"
#include "Board.h"
#include "Menu.h"


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
	//ScoreTable m_score_table;
	


	//functions
	void handleMenuMouseMoved(const sf::Vector2f);
	void handleMenuClick(const sf::Vector2f);
	void startGame();


};