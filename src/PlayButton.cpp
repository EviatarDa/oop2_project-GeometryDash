#pragma once

#include "PlayButton.h"
#include "Game.h"
#include "WithoutYouButton.h"
#include "GreyhoundButton.h"
#include "OnlyTheHorsesButton.h"
#include "SpectreButton.h"


PlayButton::PlayButton(Game* game,  sf::RenderWindow& window)
	:Command(game, window), m_levels_menu(m_game, m_window)
{
	m_levels_menu.add(WithoutYou, std::make_unique<WithoutYouButton>(m_game, m_window));
	m_levels_menu.add(Greyhound, std::make_unique<GreyhoundButton>(m_game, m_window));
	m_levels_menu.add(OnlyTheHorses, std::make_unique<OnlyTheHorsesButton>(m_game, m_window));
	m_levels_menu.add(Spectre, std::make_unique<SpectreButton>(m_game, m_window));
}

void PlayButton::execute()
{
    bool click = false;
    while (m_window.isOpen() && !click)
    {
        m_window.clear();
        m_levels_menu.drawLevelsMenu();
        m_window.display();

        if (auto event = sf::Event{}; m_window.waitEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::MouseButtonReleased:
            {
                const auto location = m_window.mapPixelToCoords(
                    { event.mouseButton.x, event.mouseButton.y });
                const int button = m_levels_menu.getOptionFromUser(location);
                m_levels_menu.performAction(button);
                click = true;
                break;
            }
            case sf::Event::MouseMoved:
            {
                const auto location = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
                m_levels_menu.handleLevelMenuMouseMoved(location);
                break;
            }
            case sf::Event::Closed:
                m_window.close();
                break;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            break;
        }
    }
}
