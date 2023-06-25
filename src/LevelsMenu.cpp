#pragma once

#include "LevelsMenu.h"

LevelsMenu::LevelsMenu(Game* game, sf::RenderWindow& window)
	: m_game(game), m_window(window)
{
	m_background.setTexture(Resources::instance().getMenuTexture(Menu_Background));
	m_background.scale(1.6f, 1.6f);

	for (int button = WithoutYou; button <= Spectre; button++)
	{
		m_buttons[button].setTexture(Resources::instance().getLevelsMenuButtons((LevelsMenuButtons)button));
		m_back_buttons[button].setTexture(Resources::instance().getLevelsMenuButtons((LevelsMenuButtons)button));
		m_back_buttons[button].setColor(sf::Color::Green);
	}
	locateObjects();
}


void LevelsMenu::drawLevelsMenu() const
{
	m_window.draw(m_background);
	for (int button = 0; button < m_options.size(); button++)
	{
		m_window.draw(m_back_buttons[button]);
		m_window.draw(m_buttons[button]);
	}
}

const int LevelsMenu::getOptionFromUser(const sf::Vector2f location)const
{
	for (int button = WithoutYou; button < m_options.size(); button++)
	{
		if (m_options[button].first.getGlobalBounds().contains(location))
		{
			return button;
		}
	}
	return m_options.size() + 1;
}

void LevelsMenu::performAction(const int action)const
{
	if (action > m_options.size())
		return;
	m_options[action].second->execute();
}

void LevelsMenu::add(const LevelsMenuButtons button, std::unique_ptr<Command> command)
{
	m_options.emplace_back(option(m_buttons[button], move(command)));
}


void LevelsMenu::handleLevelMenuMouseMoved(const sf::Vector2f location)
{
	for (int button = WithoutYou; button < m_options.size(); button++)
	{
		if (m_options[button].first.getGlobalBounds().contains(location))
		{
			ButtonPress(LevelsMenuButtons(button));
		}
		else
		{
			ButtonRelease(LevelsMenuButtons(button));
		}
	}
}

void LevelsMenu::ButtonPress(const LevelsMenuButtons button)
{
	m_buttons[button].setColor(sf::Color::Color(255, 255, 255, 150));
}

void LevelsMenu::ButtonRelease(const LevelsMenuButtons button)
{
	m_buttons[button].setColor(sf::Color::Color(255, 255, 255));
}

void LevelsMenu::locateObjects()
{
	//level buttons
	m_buttons[WithoutYou].setPosition(sf::Vector2f((WINDOW_WIDTH - m_buttons[WithoutYou].getTextureRect().width) * 0.25,
		(WINDOW_HEIGHT - m_buttons[WithoutYou].getTextureRect().height) * 0.25));

	m_buttons[Greyhound].setPosition(sf::Vector2f((WINDOW_WIDTH - m_buttons[Greyhound].getTextureRect().width) * 0.75,
		(WINDOW_HEIGHT - m_buttons[Greyhound].getTextureRect().height) * 0.25));

	m_buttons[OnlyTheHorses].setPosition(sf::Vector2f((WINDOW_WIDTH - m_buttons[OnlyTheHorses].getTextureRect().width) * 0.25,
		(WINDOW_HEIGHT - m_buttons[OnlyTheHorses].getTextureRect().height) * 0.75));

	m_buttons[Spectre].setPosition(sf::Vector2f((WINDOW_WIDTH - m_buttons[Spectre].getTextureRect().width) * 0.75,
		(WINDOW_HEIGHT - m_buttons[Spectre].getTextureRect().height) * 0.75));

	//backbuttons
	m_back_buttons[WithoutYou].setPosition(sf::Vector2f((WINDOW_WIDTH - m_buttons[WithoutYou].getTextureRect().width) * 0.25,
		(WINDOW_HEIGHT - m_buttons[WithoutYou].getTextureRect().height) * 0.25));

	m_back_buttons[Greyhound].setPosition(sf::Vector2f((WINDOW_WIDTH - m_buttons[Greyhound].getTextureRect().width) * 0.75,
		(WINDOW_HEIGHT - m_buttons[Greyhound].getTextureRect().height) * 0.25));

	m_back_buttons[OnlyTheHorses].setPosition(sf::Vector2f((WINDOW_WIDTH - m_buttons[OnlyTheHorses].getTextureRect().width) * 0.25,
		(WINDOW_HEIGHT - m_buttons[OnlyTheHorses].getTextureRect().height) * 0.75));

	m_back_buttons[Spectre].setPosition(sf::Vector2f((WINDOW_WIDTH - m_buttons[Spectre].getTextureRect().width) * 0.75,
		(WINDOW_HEIGHT - m_buttons[Spectre].getTextureRect().height) * 0.75));
}
