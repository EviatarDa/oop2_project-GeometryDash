#pragma once

#include "Menu.h"

Menu::Menu(sf::RenderWindow& window)
	:m_window(window), m_score_teble(window)
{
	m_background.setTexture(Resources::instance().getMenuTexture(Menu_Background));
	m_background.scale(1.6f, 1.6f);

	m_Authors.setTexture(Resources::instance().getMenuTexture(Authors));

	m_title.setTexture(Resources::instance().getMenuTexture(Title));

	for (int button = Play; button <= Score_Table; button++)
	{
		m_buttons[button].setTexture(Resources::instance().getMenuButtons((MenuButtons)button));
		m_back_buttons[button].setTexture(Resources::instance().getMenuButtons((MenuButtons)button));
		m_back_buttons[button].setColor(sf::Color::Green);
	}

	for (int page = OhNo; page <= DropTheMic; page++)
	{
		m_instructions[page].setTexture(Resources::instance().getMenuInstructions((MenuInstructions)page));
	}
	locateObjects();
}

void Menu::drawMenu() const
{
	m_window.draw(m_background);
	for (int button = Play; button <= Score_Table; button++)
	{
		m_window.draw(m_back_buttons[button]);
		m_window.draw(m_buttons[button]);
	}
	m_window.draw(m_title);
	//m_window.draw(m_Authors);
}

sf::Sprite Menu::getButton(const MenuButtons button) const
{
	return m_buttons[button];
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

void Menu::drawScoreTable()
{
	m_score_teble.draw();
}

void Menu::locateObjects()
{
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


	m_Authors.setPosition(sf::Vector2f((WINDOW_WIDTH - m_buttons[Score_Table].getTextureRect().width) * 0.36,
		WINDOW_HEIGHT - m_Authors.getTextureRect().height * 2));


	m_title.setPosition(sf::Vector2f((WINDOW_WIDTH - m_title.getTextureRect().width) * 0.5,
		WINDOW_HEIGHT * 0.15));

}
