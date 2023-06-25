#pragma once

#include "BoxButton.h"
#include "Game.h"


BoxButton::BoxButton(Game* game, sf::RenderWindow& window)
	:Command(game, window)
{
}

void BoxButton::execute()
{
    bool click = false;

    while (m_window.isOpen() && !click)
    {
        m_window.clear();
        m_game->getMenu().drawBoxShips();
        m_window.display();

        if (auto event = sf::Event{}; m_window.waitEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::MouseButtonReleased:
            {
                auto location = m_window.mapPixelToCoords(
                    { event.mouseButton.x, event.mouseButton.y });
                m_game->handleBoxShipPageClick(location);
                m_game->getBoard().changeBoxShip(m_game->getMenu().getPlayerTextures());
                click = true;
                break;
            }
            case sf::Event::MouseMoved:
            {
                auto location = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
                m_game->handleBoxShipMouseMoved(location);
                //m_menu.handleBoxShipMouseMoved(location);//new

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
