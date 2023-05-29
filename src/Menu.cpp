#pragma once

#include "Menu.h"

Menu::Menu()
{
	m_backgroung.setTexture(Resources::instance().getMenuTexture(Menu_Backgound));
	m_backgroung.scale(1.6f, 1.6f);

	m_Authors.setTexture(Resources::instance().getMenuTexture(Authors));

	m_title.setTexture(Resources::instance().getMenuTexture(Title));

	for (int button = Play; button <= Score_Table; button++)
	{
		m_buttons[button].setTexture(Resources::instance().getMenuButtons((MenuButtons)button));
		m_back_buttons[button].setTexture(Resources::instance().getMenuButtons((MenuButtons)button));
	}
	locateObjects();
}

void Menu::drawMenu(sf::RenderWindow& window) const
{
	window.draw(m_backgroung);
	for (int button = Play; button <= Score_Table; button++)
	{
		window.draw(m_back_buttons[button]);
		window.draw(m_buttons[button]);
	}
	window.draw(m_title);
	window.draw(m_Authors);
}

void Menu::locateObjects()
{
	m_buttons[Play].setPosition(sf::Vector2f((WINDOW_WIDTH - m_buttons[Play].getTextureRect().width) * 0.5,
		WINDOW_HEIGHT - m_buttons[Play].getTextureRect().height * 4));

	m_buttons[Help].setPosition(sf::Vector2f((WINDOW_WIDTH - m_buttons[Help].getTextureRect().width) * 0.75,
		WINDOW_HEIGHT - m_buttons[Help].getTextureRect().height * 4));;

	m_buttons[Box].setPosition(sf::Vector2f((WINDOW_WIDTH - m_buttons[Box].getTextureRect().width) * 0.25,
		WINDOW_HEIGHT - m_buttons[Box].getTextureRect().height * 4));

	m_buttons[Score_Table].setPosition(sf::Vector2f((WINDOW_WIDTH - m_buttons[Score_Table].getTextureRect().width) * 0.75,
		WINDOW_HEIGHT - m_buttons[Score_Table].getTextureRect().height * 1.5));



	m_back_buttons[Play].setPosition(sf::Vector2f((WINDOW_WIDTH - m_buttons[Play].getTextureRect().width) * 0.5,
		WINDOW_HEIGHT - m_back_buttons[Play].getTextureRect().height * 4));

	m_back_buttons[Help].setPosition(sf::Vector2f((WINDOW_WIDTH - m_buttons[Help].getTextureRect().width) * 0.75,
		WINDOW_HEIGHT - m_back_buttons[Help].getTextureRect().height * 4));

	m_back_buttons[Box].setPosition(sf::Vector2f((WINDOW_WIDTH - m_buttons[Box].getTextureRect().width) * 0.25,
		WINDOW_HEIGHT - m_back_buttons[Box].getTextureRect().height * 4));

	m_back_buttons[Score_Table].setPosition(sf::Vector2f((WINDOW_WIDTH - m_buttons[Score_Table].getTextureRect().width) * 0.75,
		WINDOW_HEIGHT - m_back_buttons[Score_Table].getTextureRect().height * 1.5));
	


	m_Authors.setPosition(sf::Vector2f((WINDOW_WIDTH - m_buttons[Score_Table].getTextureRect().width) * 0.25,
		WINDOW_HEIGHT - m_Authors.getTextureRect().height * 1.5 ));


	m_title.setPosition(sf::Vector2f((WINDOW_WIDTH - m_title.getTextureRect().width) * 0.5,
		WINDOW_HEIGHT * 0.15));

}
