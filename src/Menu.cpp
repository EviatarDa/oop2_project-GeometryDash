#pragma once

#include "Menu.h"

Menu::Menu(sf::RenderWindow& window)
	:m_window(window), m_score_table(window), m_box_ship(BoxShip1)
{
	//setting menu textures
	m_background.setTexture(Resources::instance().getMenuTexture(Menu_Background));
	m_background.scale(1.6f, 1.6f);

	m_title.setTexture(Resources::instance().getMenuTexture(Title));

	for (int button = Play; button <= Spectre; button++)
	{
		m_buttons[button].setTexture(Resources::instance().getMenuButtons((MenuButtons)button));
		m_back_buttons[button].setTexture(Resources::instance().getMenuButtons((MenuButtons)button));
		m_back_buttons[button].setColor(sf::Color::Green);
	}

	for (int page = OhNo; page <= DropTheMic; page++)
	{
		m_instructions[page].setTexture(Resources::instance().getMenuInstructions((MenuInstructions)page));
	}

	for (int box_ship = BoxShip1; box_ship <= BoxShip6; box_ship++)
	{
		m_box_ships[box_ship].setTexture(Resources::instance().getMenuBoxShips((MenuBoxShips)box_ship));
		m_box_ships[box_ship].scale(0.5, 0.5);

		m_box_ships_rect[box_ship].setSize(sf::Vector2f(m_box_ships[box_ship].getGlobalBounds().width,
			m_box_ships[box_ship].getGlobalBounds().height));
		m_box_ships_rect[box_ship].setFillColor(sf::Color::Transparent);
		m_box_ships_rect[box_ship].setOutlineColor(sf::Color::White);
		m_box_ships_rect[box_ship].setOutlineColor(sf::Color::Color(255, 255, 255, 0));
		m_box_ships_rect[box_ship].setOutlineThickness(2.f);
	}

	m_box_ship_text.setFont(Resources::instance().getFont());
	m_box_ship_text.setCharacterSize(104);
	m_box_ship_text.setOutlineThickness(2);
	m_box_ship_text.setOutlineColor(sf::Color::Red);
	m_box_ship_text.setString("Choose Your Player:");
	
	m_menu_sound.setBuffer(Resources::instance().getGameSounds(Echo_Song));
	m_menu_sound.setLoop(true);

	locateObjects();
}



void Menu::drawMenu() const
{
	m_window.draw(m_background);
	for (int button = 0; button < m_options.size(); button++)
	{
		m_window.draw(m_back_buttons[button]);
		m_window.draw(m_buttons[button]);
	}
	m_window.draw(m_title);
}

const int Menu::getOptionFromUser(const sf::Vector2f location) const
{
	//check if the button contains the click location 
	for (int button = Play; button < m_options.size(); button++)
	{
		if (m_options[button].first.getGlobalBounds().contains(location))
		{
			//return the button we clicked at
			return button;
		}
	}
	//no button
	return m_options.size() + 1;
}

void Menu::performAction(const int action)const
{
	//if no button pressed
	if (action > m_options.size())
		return;

	m_options[action].second->execute();
}

void Menu::add(const MenuButtons button, std::unique_ptr<Command> command)
{
	//adding new button to the menu
	m_options.emplace_back(option(m_buttons[button], move(command)));
}

void Menu::handleMenuMouseMoved(const sf::Vector2f location)
{
	//indicate the location of the mouse 
	for (int button = Play; button < m_options.size(); button++)
	{
		if (m_options[button].first.getGlobalBounds().contains(location))
		{
			//bolding the button
			ButtonPress(MenuButtons(button));
		}
		else
		{
			//unbolding the button
			ButtonRelease(MenuButtons(button));
		}
	}
}

const sf::Sprite Menu::getBoxShip(const MenuBoxShips box_ship) const
{
	//return the sprite
	return m_box_ships[box_ship];
}

void Menu::boxShipPress(const MenuBoxShips box_ship)
{
	m_box_ships_rect[box_ship].setOutlineColor(sf::Color::Color(255, 255, 255, 255));
}

void Menu::boxShipRelease(const MenuBoxShips box_ship)
{
	m_box_ships_rect[box_ship].setOutlineColor(sf::Color::Color(255, 255, 255, 0));
}

void Menu::ButtonPress(const MenuButtons button)
{
	m_buttons[button].setColor(sf::Color::Color(255, 255, 255, 150));
}

void Menu::ButtonRelease(const MenuButtons button)
{
	m_buttons[button].setColor(sf::Color::Color(255, 255, 255));
}

void Menu::drawInstructions(const MenuInstructions page) const
{
	m_window.draw(m_background);
	m_window.draw(m_instructions[page]);
}

void Menu::drawScoreTable()const
{
	m_score_table.draw();
}

void Menu::drawBoxShips()const
{
	m_window.draw(m_background);
	for (int box_ship = BoxShip1; box_ship <= BoxShip6; box_ship++)
	{
		m_window.draw(m_box_ships[box_ship]);
		m_window.draw(m_box_ships_rect[box_ship]);
	}
	m_window.draw(m_box_ship_text);
}


const std::pair<GameTextures, GameTextures> Menu::getPlayerTextures() const
{
	//returning the player textures picked by pair of box and ship
	switch (m_box_ship)
	{
	case BoxShip1:
		return std::pair<GameTextures, GameTextures>(PlayerBox1, PlayerShip1);
		break;

	case BoxShip2:
		return std::pair<GameTextures, GameTextures>(PlayerBox2, PlayerShip2);
		break;

	case BoxShip3:
		return std::pair<GameTextures, GameTextures>(PlayerBox3, PlayerShip3);
		break;

	case BoxShip4:
		return std::pair<GameTextures, GameTextures>(PlayerBox4, PlayerShip4);
		break;

	case BoxShip5:
		return std::pair<GameTextures, GameTextures>(PlayerBox5, PlayerShip5);
		break;

	case BoxShip6:
		return std::pair<GameTextures, GameTextures>(PlayerBox6, PlayerShip6);
		break;
	}
}

void Menu::chooseBoxShip(const MenuBoxShips box_ship)
{
	//updating the player
	m_box_ship = box_ship;
}

void Menu::updateScoreTable(const int score, std::string player_name)
{
	//if no name inserted
	if (player_name == "")
		player_name = "Unknown Player";

	m_score_table.addScore(player_name, score);
	m_score_table.saveScoresToFile();
}

void Menu::playSong()
{
	//reset the song before start
	stopSong();
	m_menu_sound.play();
}

void Menu::stopSong()
{
	m_menu_sound.stop();
}

void Menu::locateObjects()
{
	//buttons
	m_buttons[Play].setPosition(sf::Vector2f((WINDOW_WIDTH - m_buttons[Play].getTextureRect().width) * 0.5,
		WINDOW_HEIGHT - m_buttons[Help].getTextureRect().height * 4));

	m_buttons[Help].setPosition(sf::Vector2f((WINDOW_WIDTH - m_buttons[Help].getTextureRect().width) * 0.75,
		WINDOW_HEIGHT - m_buttons[Help].getTextureRect().height * 4));;

	m_buttons[Box].setPosition(sf::Vector2f((WINDOW_WIDTH - m_buttons[Box].getTextureRect().width) * 0.25,
		WINDOW_HEIGHT - m_buttons[Box].getTextureRect().height * 4));

	m_buttons[Score_Table].setPosition(sf::Vector2f((WINDOW_WIDTH - m_buttons[Score_Table].getTextureRect().width) * 0.5,
		WINDOW_HEIGHT - m_buttons[Score_Table].getTextureRect().height * 2));


	//backbutton
	m_back_buttons[Play].setPosition(sf::Vector2f((WINDOW_WIDTH - m_buttons[Play].getTextureRect().width) * 0.5,
		WINDOW_HEIGHT - m_back_buttons[Help].getTextureRect().height * 4));

	m_back_buttons[Help].setPosition(sf::Vector2f((WINDOW_WIDTH - m_buttons[Help].getTextureRect().width) * 0.75,
		WINDOW_HEIGHT - m_back_buttons[Help].getTextureRect().height * 4));

	m_back_buttons[Box].setPosition(sf::Vector2f((WINDOW_WIDTH - m_buttons[Box].getTextureRect().width) * 0.25,
		WINDOW_HEIGHT - m_back_buttons[Box].getTextureRect().height * 4));

	m_back_buttons[Score_Table].setPosition(sf::Vector2f((WINDOW_WIDTH - m_buttons[Score_Table].getTextureRect().width) * 0.5,
		WINDOW_HEIGHT - m_back_buttons[Score_Table].getTextureRect().height * 2));

	//title
	m_title.setPosition(sf::Vector2f((WINDOW_WIDTH - m_title.getTextureRect().width) * 0.5,
		WINDOW_HEIGHT * 0.15));

	//BoxShips
	m_box_ships[BoxShip1].setPosition(sf::Vector2f(WINDOW_WIDTH * 0.1f, WINDOW_HEIGHT / 2.5f));
	m_box_ships[BoxShip2].setPosition(sf::Vector2f(WINDOW_WIDTH * 0.4f, WINDOW_HEIGHT / 2.5f));
	m_box_ships[BoxShip3].setPosition(sf::Vector2f(WINDOW_WIDTH * 0.7f, WINDOW_HEIGHT / 2.5f));
	m_box_ships[BoxShip4].setPosition(sf::Vector2f(WINDOW_WIDTH * 0.1, WINDOW_HEIGHT * 3.f / 4.f));
	m_box_ships[BoxShip5].setPosition(sf::Vector2f(WINDOW_WIDTH * 0.4f, WINDOW_HEIGHT * 3.f / 4.f));
	m_box_ships[BoxShip6].setPosition(sf::Vector2f(WINDOW_WIDTH * 0.7f, WINDOW_HEIGHT * 3.f / 4.f));

	//rectangles
	for (int box_ship = BoxShip1; box_ship <= BoxShip6; box_ship++)
	{
		m_box_ships_rect[box_ship].setPosition(sf::Vector2f(m_box_ships[box_ship].getGlobalBounds().left,
			m_box_ships[box_ship].getGlobalBounds().top));
	}

	//choose player text
	m_box_ship_text.setPosition(sf::Vector2f(WINDOW_WIDTH/2 - m_box_ship_text.getLocalBounds().width/2,
		WINDOW_HEIGHT*0.15));
}
