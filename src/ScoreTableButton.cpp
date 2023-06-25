#pragma once

#include "ScoreTableButton.h"
#include "Game.h"

ScoreTableButton::ScoreTableButton(Game* game, sf::RenderWindow& window)
	:Command(game, window)
{
}

void ScoreTableButton::execute()
{
    bool click = false;

    while (m_window.isOpen() && !click)
    {
        m_window.clear();
        m_game->getMenu().drawScoreTable();
        m_window.display();

        if (auto event = sf::Event{}; m_window.waitEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::MouseButtonReleased:
            {
                click = true;
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
