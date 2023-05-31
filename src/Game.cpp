#pragma once

#include "Game.h"

Game::Game()
    :m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Geometry Dash"),
    m_score_table(m_window)
{
    m_window.setFramerateLimit(120);
    m_gameView.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    m_gameView.setCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT/2);
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
            m_window.clear();
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
    bool flag = true;
    while (m_window.isOpen())
    {
        m_window.clear(sf::Color::Color(0, 102, 102));
        m_window.setView(m_gameView);
        m_board.drawBoard(this->m_window);
        m_window.display();
        m_board.moveObjects();
        setView();



        for (auto event = sf::Event{}; m_window.pollEvent(event); )
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_window.close();
                break;

            case sf::Event::KeyPressed:
            {
                // Move player box up
                if (flag && event.key.code == sf::Keyboard::Space)
                {
                    flag = false;
                    m_board.jumpPlayer();
                }
                if (event.key.code == sf::Keyboard::Right)
                {
                    m_board.movePlayerRight();
                }
                break;
            }
            case sf::Event::KeyReleased:
                flag = true;

            }
        }
    }
}

void Game::setView()
{
    float last_pos = m_gameView.getCenter().x;
    b2Vec2 playerPosition = m_board.getPlayerPosition();
    float playerX = playerPosition.x * SCALE;
    m_gameView.setCenter( playerX , WINDOW_HEIGHT / 2);
    m_board.viewBackground(playerX - last_pos); //make the background move with the view
}
