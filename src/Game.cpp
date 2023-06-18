#pragma once

#include "Game.h"

Game::Game()
    :m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Geometry Dash"),
    m_menu(m_window),
    m_board(m_window, m_menu.getPlayerTextures())
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
        m_menu.drawMenu();
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
                handleMenuMouseMoved(location, Play, Score_Table);
            }

            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            m_window.close();
        }
    }
}

void Game::handleMenuMouseMoved(const sf::Vector2f location, int first, int last)
{
    for (int button = first; button <= last; button++)
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

void Game::handleBoxShipMouseMoved(const sf::Vector2f location)
{
    for (int box_ship = BoxShip1; box_ship <= BoxShip6; box_ship++)
    {
        if ((m_menu.getBoxShip((MenuBoxShips)box_ship).getGlobalBounds().contains(location)))
        {
            m_menu.boxShipPress((MenuBoxShips)box_ship);
        }
        else
        {
            m_menu.boxShipRelease((MenuBoxShips)box_ship);
        }
    }
}

void Game::handleMenuClick(const sf::Vector2f location)
{
    if (m_menu.getButton(Play).getGlobalBounds().contains(location))
    {
        chooseLevel();
    }
    else if (m_menu.getButton(Help).getGlobalBounds().contains(location))
    {
        instructions();
    }
    else if (m_menu.getButton(Box).getGlobalBounds().contains(location))
    {
        chooseBoxShip();
    }
    else if (m_menu.getButton(Score_Table).getGlobalBounds().contains(location))
    {
        scoreTable();
    }
}

void Game::handleBoxShipPageClick(const sf::Vector2f location)
{
    for (int box_ship = BoxShip1; box_ship < MENU_BOX_SHIPS; box_ship++)
    {
        if (m_menu.getBoxShip((MenuBoxShips)box_ship).getGlobalBounds().contains(location))
        {
            m_menu.chooseBoxShip((MenuBoxShips)box_ship);
        }
    }
}

void Game::handleLevelsPageClick(const sf::Vector2f location)
{
    if (m_menu.getButton(WithoutYou).getGlobalBounds().contains(location))
    {
        m_board.createLevel(Map1);
    }
    else if (m_menu.getButton(Greyhound).getGlobalBounds().contains(location))
    {
        m_board.createLevel(Map2);
    }
    else if (m_menu.getButton(OnlyTheHorses).getGlobalBounds().contains(location))
    {
        m_board.createLevel(Map1);
    }
    else if (m_menu.getButton(Spectre).getGlobalBounds().contains(location))
    {
        m_board.createLevel(Map1);
    }
    startGame();
}



void Game::startGame()
{
    while (m_window.isOpen())
    {
        m_window.clear(sf::Color::Color(0, 102, 102));
        m_window.setView(m_gameView);
        m_board.drawBoard();
        m_window.display();

        m_board.updateMovingDirections();
        m_board.moveObjects();
        m_board.handleCollision();
        setView();


        for (auto event = sf::Event{}; m_window.pollEvent(event); )
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_window.close();
                break;
            case sf::Event::KeyReleased:
            {
                if (event.key.code == sf::Keyboard::Right)
                {
                    m_board.rightReleased();
                }
                else if (event.key.code == sf::Keyboard::Left)
                {
                    m_board.leftReleased();
                }
                else if (event.key.code == sf::Keyboard::Space)
                {
                    m_board.spaceReleased();
                }
                break;
            }
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

void Game::instructions()
{
    int page = OhNo;

    while (m_window.isOpen() && page <= DropTheMic)
    {
        m_window.clear();
        m_menu.drawInstructions((MenuInstructions)page);
        m_window.display();

        if (auto event = sf::Event{}; m_window.waitEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::MouseButtonReleased:
            {
                page++;
                break;
            }
            case sf::Event::Closed:
                m_window.close();
                break;
            }

        }
    }
}

void Game::scoreTable()
{
    bool click = false;

    while (m_window.isOpen() && !click)
    {
        m_window.clear();
        m_menu.drawScoreTable();
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

void Game::chooseBoxShip()
{
    bool click = false;

    while (m_window.isOpen() && !click)
    {
        m_window.clear();
        m_menu.drawBoxShips();
        m_window.display();

        if (auto event = sf::Event{}; m_window.waitEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::MouseButtonReleased:
            {
                auto location = m_window.mapPixelToCoords(
                    { event.mouseButton.x, event.mouseButton.y });
                handleBoxShipPageClick(location);
                m_board.changeBoxShip(m_menu.getPlayerTextures());
                click = true;
                break;
            }
            case sf::Event::MouseMoved:
            {
                auto location = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
                handleBoxShipMouseMoved(location);
                break;
            }
            case sf::Event::Closed:
                m_window.close();
                break;
            }
        }
    }
}

void Game::chooseLevel()
{
    bool click = false;

    while (m_window.isOpen() && !click)
    {
        m_window.clear();
        m_menu.drawLevelsPage();
        m_window.display();

        if (auto event = sf::Event{}; m_window.waitEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::MouseButtonReleased:
            {
                auto location = m_window.mapPixelToCoords(
                    { event.mouseButton.x, event.mouseButton.y });
                handleLevelsPageClick(location);
                click = true;
                break;
            }
            case sf::Event::MouseMoved:
            {
                auto location = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
                handleMenuMouseMoved(location, WithoutYou, Spectre);
                break;
            }
            case sf::Event::Closed:
                m_window.close();
                break;
            }
        }
    }
}


