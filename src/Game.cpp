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

    //adding menu buttons:
    m_menu.add(Play, std::make_unique<PlayButton>(this, m_window));
    m_menu.add(Help, std::make_unique<HelpButton>(this, m_window));
    m_menu.add(Box, std::make_unique<BoxButton>(this, m_window));
    m_menu.add(Score_Table, std::make_unique<ScoreTableButton>(this, m_window));
}

void Game::runMenu()
{
    m_menu.playSong();
    while (m_window.isOpen())
    {
        m_window.clear();
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
                //getting the click location, checking what button pressed
                const auto location = m_window.mapPixelToCoords(
                    { event.mouseButton.x, event.mouseButton.y });
                const int button = m_menu.getOptionFromUser(location);

                //performing the button action acordingly
                m_menu.performAction(button);
                break;
            }

            case sf::Event::MouseMoved:
            {
                //indicate if the mouse on the buttons 
                const auto location = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
                m_menu.handleMenuMouseMoved(location);
                break;
            }

            }
        }
    }
}

void Game::handleBoxShipMouseMoved(const sf::Vector2f location)
{
    for (int box_ship = BoxShip1; box_ship <= BoxShip6; box_ship++)
    {
        if ((m_menu.getBoxShip((MenuBoxShips)box_ship).getGlobalBounds().contains(location)))
        {
            //bolding the corrent button
            m_menu.boxShipPress((MenuBoxShips)box_ship);
        }
        else
        {
            //unbolding the button
            m_menu.boxShipRelease((MenuBoxShips)box_ship);
        }
    }
}

void Game::handleBoxShipPageClick(const sf::Vector2f location)
{
    for (int box_ship = BoxShip1; box_ship < MENU_BOX_SHIPS; box_ship++)
    {
        if (m_menu.getBoxShip((MenuBoxShips)box_ship).getGlobalBounds().contains(location))
        {
            //saving the player pick at the menu
            m_menu.chooseBoxShip((MenuBoxShips)box_ship);
        }
    }
}


void Game::startGame()
{
    //init
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
                //update the player direction
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
        m_board.handleCollision(); //hndling collisions that needs to be solved at board
        setView(); // update the game view and background 

        //if player reached the end gate
        if (m_board.isWin())
        {
            m_game_over = true;
            //reset game view
            m_gameView.setCenter(WINDOW_WIDTH/2,WINDOW_HEIGHT/2);
            m_window.setView(m_gameView);
            winLoop(); //taking name to scoreboard
        }
        if (m_game_over)
        {
            //reset board for next game
            m_board.resetBoard();
            //reset game view - (if the player exit with escape)
            m_gameView.setCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
            m_window.setView(m_gameView);
        }
    }
}

void Game::setView()
{
    // keeping the last positions
    const float last_pos = m_gameView.getCenter().x;
    const b2Vec2 playerPosition = m_board.getPlayerPosition();
    const float playerX = playerPosition.x * SCALE;
    m_gameView.setCenter(playerX, WINDOW_HEIGHT / 2);
    m_board.viewBackground(playerX - last_pos); //make the background move with the view
}

Board& Game::getBoard() 
{
    return m_board;
}

Menu& Game::getMenu()
{
    return m_menu;
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
                //getting the click location, checking what button pressed
                const auto location = m_window.mapPixelToCoords(
                    { event.mouseButton.x, event.mouseButton.y });

                //performing the button action acordingly
                handleBoxShipPageClick(location);
                m_board.changeBoxShip(m_menu.getPlayerTextures());
                click = true;
                break;
            }
            case sf::Event::MouseMoved:
            {
                //indicate if the mouse on the buttons 
                const auto location = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
                handleBoxShipMouseMoved(location);
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

void Game::winLoop() 
{
    //loop to get the player name and enter him to score board:
    bool done = false;
    bool show_cursor = true;
    int char_counter = 0;
    int score = 0;

    //objects to render
    sf::Sprite score_board, background;
    sf::Text time_score, coin_score;
    sf::Text name;
    sf::Text enter_name;
    sf::RectangleShape input_rectangle;
    sf::RectangleShape cursor;
    sf::Clock cursor_clock;

    //keep the player name
    std::string player_name;

    //reset and locate the object
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

        //make the cursor look like cursor
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
                //if the text is keyboard letter
                if (event.text.unicode < 128)
                {
                    //delete the letter
                    if (event.text.unicode == '\b' && !player_name.empty())
                    {
                        player_name.pop_back();
                        char_counter--;
                    }
                    //insert the letter
                    else if (event.text.unicode != '\b' && char_counter < 20)
                    {
                        player_name += static_cast<char>(event.text.unicode);
                        char_counter++;
                    }

                    //enter the letter to string
                    name.setString(player_name);
                    cursor_clock.restart();
                }
                break;
            }
            case sf::Event::KeyPressed:
            {
                if (event.key.code == sf::Keyboard::Enter )
                {
                    //insert the score to score table
                    done = true;
                    m_menu.updateScoreTable(score, player_name);

                }
                break;
            }
        }
        }

        //blink the cursor
        if (cursor_clock.getElapsedTime().asSeconds() >= 0.5f)
        {
            show_cursor = !show_cursor;
            cursor_clock.restart();
        }
    }
}

void Game::createScoreBoard(sf::Sprite& score_board, sf::Sprite& background, sf::Text& time_score, sf::Text& coin_score, int& score,
    sf::Text& name, sf::Text& enter_name, sf::RectangleShape& input_rectangle, sf::RectangleShape& cursor) const
{
    //set textures and locate the sprites
    score_board.setTexture(Resources::instance().getGameTexture(ScoreBoard));
    background.setTexture(Resources::instance().getGameTexture(Level_Background));
    background.scale(1.6f, 1.6f);

    time_score.setFont(Resources::instance().getFont());
    time_score.setOutlineColor(sf::Color::Black);
    time_score.setOutlineThickness(1.f);

    coin_score.setFont(Resources::instance().getFont());
    coin_score.setOutlineColor(sf::Color::Black);
    coin_score.setOutlineThickness(1.f);

    const int game_elapsed_time = m_game_clock.getElapsedTime().asSeconds();

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


