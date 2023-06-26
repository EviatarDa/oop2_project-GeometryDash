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
                //getting the click location, checking what button pressed
                const auto location = m_window.mapPixelToCoords(
                    { event.mouseButton.x, event.mouseButton.y });

                //performing the button action acordingly
                m_game->handleBoxShipPageClick(location);
                m_game->getBoard().changeBoxShip(m_game->getMenu().getPlayerTextures());
                click = true;
                break;
            }
            case sf::Event::MouseMoved:
            {
                //indicate if the mouse on the buttons 
                const auto location = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
                m_game->handleBoxShipMouseMoved(location);
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
