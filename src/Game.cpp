#pragma once

#include "Game.h"

Game::Game()
    :m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Geometry Dash"),
    m_score_table(m_window)
{
    m_window.setFramerateLimit(120);
}

void Game::runMenu()
{
    while (m_window.isOpen())
    {
        m_window.clear(sf::Color::Color(0, 0, 0));
        m_menu.drawMenu(this->m_window);
        m_window.display();

        if (auto event = sf::Event{}; m_window.waitEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_window.close();
                break;

            case sf::Event::MouseButtonReleased:
            {
                auto location = m_window.mapPixelToCoords(
                    { event.mouseButton.x, event.mouseButton.y });
                handleMenuClick(location);
                break;
            }

            case sf::Event::MouseMoved:
            {
                auto location = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
                handleMenuMouseMoved(location);
            }

            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            m_window.close();
        }
    }
}

void Game::handleMenuMouseMoved(const sf::Vector2f location)
{
    for (int button = Play; button <= Score_Table; button++)
    {
        if ((m_menu.getButton((MenuButtons)button).getGlobalBounds().contains(location)))
        {
            m_menu.ButtonPress((MenuButtons)button);
        }
        else
        {
            m_menu.ButtonRelease((MenuButtons)button);
        }
    }
}

void Game::handleMenuClick(const sf::Vector2f location)
{
    if (m_menu.getButton(Play).getGlobalBounds().contains(location))
    {
        startGame();
    }
    else if (m_menu.getButton(Help).getGlobalBounds().contains(location))
    {
    }
    else if (m_menu.getButton(Box).getGlobalBounds().contains(location))
    {
    }
    else if (m_menu.getButton(Score_Table).getGlobalBounds().contains(location))
    {
        bool click = false;

        while (!click)
        {
            m_window.clear(WINDOW_COLOR);
            m_score_table.draw();
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
        }
        
    }
}

void Game::startGame()
{
    while (m_window.isOpen())
    {
        m_window.clear(sf::Color::Color(0, 102, 102)); // blue
        m_board.drawBoard(this->m_window);
        m_window.display();

        for (auto event = sf::Event{}; m_window.pollEvent(event); )
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_window.close();
                break;
            }
        }
    }
}