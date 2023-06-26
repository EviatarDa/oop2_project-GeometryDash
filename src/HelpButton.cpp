#pragma once

#include "HelpButton.h"
#include "Game.h"

HelpButton::HelpButton(Game* game, sf::RenderWindow& window)
	:Command(game, window)
{
}

void HelpButton::execute()
{
    int page = OhNo;

    //drowing the instructions pages and moving forward with click
    while (m_window.isOpen() && page <= DropTheMic)
    {
        m_window.clear();
        m_game->getMenu().drawInstructions((MenuInstructions)page);
        m_window.display();

        if (auto event = sf::Event{}; m_window.waitEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::MouseButtonReleased:
            {
                //moving to next page
                page++;
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
