#pragma once

#include "Game.h"

Game::Game()
    :m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Geometry Dash"),
    m_menu(m_window),
    m_board(m_window, m_menu.getPlayerTextures())
    //m_screen_menager(std::make_unique<MenuState>())
{
    m_window.setFramerateLimit(120);
    m_gameView.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    m_gameView.setCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT/2);


}

void Game::runMenu()
{
    m_menu.playSong();
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
        m_board.createLevel(Map1, WithoutYou_Song);

    else if (m_menu.getButton(Greyhound).getGlobalBounds().contains(location))
        m_board.createLevel(Map2, Greyhound_Song);

    else if (m_menu.getButton(OnlyTheHorses).getGlobalBounds().contains(location))
        m_board.createLevel(Map3, OnlyTheHorses_Song );

    else if (m_menu.getButton(Spectre).getGlobalBounds().contains(location))
        m_board.createLevel(Map4, Spectre_Song);

    else
        return;
    m_menu.stopSong();
    startGame();
    m_menu.playSong();
}


void Game::startGame()
{
    m_game_clock.restart();
    m_game_over = false;

    while (m_window.isOpen() && !m_game_over)
    {
        m_window.clear(sf::Color::Color(0, 102, 102));
        m_window.setView(m_gameView);
        m_board.drawBoard();
        m_window.display();

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
                else if (event.key.code == sf::Keyboard::Escape)
                {
                    m_game_over = true;
                }
                break;
            }
            }

        }

        m_board.updateMovingDirections();
        m_board.moveObjects();
        m_board.handleCollision();
        setView();

        if (m_board.isWin())
        {
            m_gameView.setCenter(WINDOW_WIDTH/2,WINDOW_HEIGHT/2);
            m_window.setView(m_gameView);
            winLoop();
        }
        if (m_game_over)
        {
            m_board.resetBoard();
            m_gameView.setCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
            m_window.setView(m_gameView);
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

void Game::winLoop() 
{
    m_game_over = true;
    bool done = false;
    sf::Sprite score_board, background;
    sf::Text time_score, coin_score;
    int score = 0;
    sf::Text name;
    sf::RectangleShape input_rectangle;
    sf::RectangleShape cursor;
    sf::Clock cursor_clock;
    std::string player_name;
    bool show_cursor = true;
    sf::Text enter_name;
    int char_counter = 0;

    createScoreBoard(score_board, background, time_score, coin_score,
        score, name, enter_name, input_rectangle, cursor);

    while (!done)
    {
        m_window.clear();
        m_window.draw(background);
        m_window.draw(score_board);
        m_window.draw(time_score);
        m_window.draw(coin_score);
        m_window.draw(input_rectangle);
        m_window.draw(name);
        m_window.draw(enter_name);

        if (show_cursor)
        {
            m_window.draw(cursor);
        }

        m_window.display();

        sf::Event event;
        while (m_window.pollEvent(event))
        {
            switch (event.type)
            {

            case sf::Event::Closed:
                m_window.close();
                break;

            case sf::Event::TextEntered:
            {
                if (event.text.unicode < 128)
                {
                    if (event.text.unicode == '\b' && !player_name.empty())
                    {
                        player_name.pop_back();
                        char_counter--;
                    }
                    else if (event.text.unicode != '\b' && char_counter < 20)
                    {
                        player_name += static_cast<char>(event.text.unicode);
                        char_counter++;
                    }

                    name.setString(player_name);
                    cursor_clock.restart();
                }
            }
            case sf::Event::KeyPressed:
            {
                if (event.key.code == sf::Keyboard::Enter)
                {
                    done = true;
                    m_menu.updateScoreTable(score, player_name);

                }
            }
        }
        }

        if (cursor_clock.getElapsedTime().asSeconds() >= 0.5f)
        {
            show_cursor = !show_cursor;
            cursor_clock.restart();
        }
    }
}

void Game::createScoreBoard(sf::Sprite& score_board, sf::Sprite& background, sf::Text& time_score, sf::Text& coin_score, int& score,
    sf::Text& name, sf::Text& enter_name, sf::RectangleShape& input_rectangle, sf::RectangleShape& cursor)
{
    score_board.setTexture(Resources::instance().getGameTexture(ScoreBoard));
    background.setTexture(Resources::instance().getGameTexture(Level_Background));
    background.scale(1.6f, 1.6f);

    time_score.setFont(Resources::instance().getFont());
    time_score.setOutlineColor(sf::Color::Black);
    time_score.setOutlineThickness(1.f);

    coin_score.setFont(Resources::instance().getFont());
    coin_score.setOutlineColor(sf::Color::Black);
    coin_score.setOutlineThickness(1.f);

    int game_elapsed_time = m_game_clock.getElapsedTime().asSeconds();

    score = 10000 - (game_elapsed_time * 2) + m_board.getCoins() * 5;

    time_score.setString(std::to_string(score));
    coin_score.setString(std::to_string(m_board.getCoins()));

    score_board.setPosition(sf::Vector2f((WINDOW_WIDTH - score_board.getTextureRect().width) * 0.5,
        (WINDOW_HEIGHT - score_board.getTextureRect().height) * 0.3));

    time_score.setPosition(sf::Vector2f(score_board.getPosition().x + score_board.getTextureRect().width / 2.5,
        score_board.getPosition().y + score_board.getTextureRect().height / 2.2));

    coin_score.setPosition(sf::Vector2f(score_board.getPosition().x + score_board.getTextureRect().width / 2.4,
        score_board.getPosition().y + score_board.getTextureRect().height / 1.4));
    
    enter_name.setString("Enter your name:");
    enter_name.setFont(Resources::instance().getFont());
    enter_name.setCharacterSize(35);
    enter_name.setFillColor(sf::Color::White);
    enter_name.setOutlineColor(sf::Color::Black);
    enter_name.setOutlineThickness(2.f);
    enter_name.setPosition(sf::Vector2f((WINDOW_WIDTH - enter_name.getLocalBounds().width) * 0.5,
        (WINDOW_HEIGHT - enter_name.getLocalBounds().height) * 0.52));

    input_rectangle.setSize(sf::Vector2f(300, 30));
    input_rectangle.setFillColor(sf::Color::White);
    input_rectangle.setPosition(sf::Vector2f((WINDOW_WIDTH - input_rectangle.getLocalBounds().width) * 0.5,
        (WINDOW_HEIGHT - input_rectangle.getLocalBounds().height) * 0.6));

    name.setFont(Resources::instance().getFont());
    name.setCharacterSize(24);
    name.setFillColor(sf::Color::Black);
    name.setPosition(sf::Vector2f((WINDOW_WIDTH - input_rectangle.getLocalBounds().width) * 0.5,
        (WINDOW_HEIGHT - input_rectangle.getLocalBounds().height) * 0.6));

    cursor.setSize(sf::Vector2f(2, 24));
    cursor.setFillColor(sf::Color::Black);
    cursor.setPosition(sf::Vector2f((WINDOW_WIDTH - input_rectangle.getLocalBounds().width) * 0.5 + 4,
        (WINDOW_HEIGHT - input_rectangle.getLocalBounds().height) * 0.6 + 4));

    
}


