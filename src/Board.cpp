#pragma once

#include "Board.h"

Board::Board(sf::RenderWindow& window, const std::pair<GameTextures, GameTextures> player_texture)
	:m_window(window), m_gravity(0.0f,9.8f), m_world(m_gravity), m_player_textures(player_texture)
{
    m_background.setTexture(Resources::instance().getGameTexture(Level_Background));
    m_background.scale(1.6f, 1.6f);
    m_background.setColor(sf::Color::White);
    m_world.SetContactListener(&m_contact); //for the override function
}


void Board::drawBoard() const
{
    m_window.draw(m_background);
    for (int object = 0; object < m_static_objects.size(); object++)
    {
        m_static_objects[object]->draw(m_window);
    }
    for (int object = 0; object < m_moving_objects.size(); object++)
    {
        m_moving_objects[object]->draw(m_window);
    }
}

void Board::moveObjects()
{
    // Update Box2D world
    float timeStep = 1.0f / 60.0f; // Adjust the time step as needed
    int32 velocityIterations = 6; // Adjust the iterations as needed
    int32 positionIterations = 2; // Adjust the iterations as needed
    m_world.Step(timeStep, velocityIterations, positionIterations);

    for (int index = 0; index < m_moving_objects.size(); index++)
    {
        m_moving_objects[index]->move();
    }
}


const b2Vec2 Board::getPlayerPosition()const
{
    return m_player->getPosition();
}

void Board::viewBackground(const float addition)
{
    //moving the game background
    m_background.setPosition(m_background.getPosition().x + addition , m_background.getPosition().y);
}

void Board::swapGravity()
{
    //
    m_gravity = -m_gravity;
    m_world.SetGravity(m_gravity);
}

void Board::updateMovingDirections()const
{
    //update each moving object direction 
    for (int object = 0; object < m_moving_objects.size(); ++object)
    {
        m_moving_objects[object]->updateDirection();
    }
}

void Board::rightReleased()const
{
    m_player->releaseRight();
}

void Board::leftReleased()const
{
    m_player->releaseLeft();
}

void Board::spaceReleased()const
{
    m_player->releaseSpace();
}

void Board::changeBoxShip(const std::pair<GameTextures, GameTextures> player_textures)
{
    //change the player box ship
    m_player_textures = player_textures;
}

void Board::handleCollision()
{
    //delete coins
    std::erase_if(m_static_objects, [](const auto& static_object) {return static_object->getDelete(); });
       
    //update every collision that needes to be care out of the contact listener function
    if (!m_player->isAlive())
    {
        m_player->kill();
        m_background.setColor(sf::Color::White);
    }

    //change player to box state
    if (m_player->isBoxStateMarked())
    {
        m_player->handleBoxStateMarking();
        m_background.setColor(sf::Color(rand(), rand(), rand()));
    }

    //change player to ship state
    if (m_player->isShipStateMarked())
    {
        m_player->handleShipStateMarking();
        m_background.setColor(sf::Color(rand(), rand(), rand()));
    }
    
    //changing gravity
    if (m_player->isGravityMarked())
    {
        swapGravity();
        m_background.setColor(sf::Color(rand(), rand(), rand()));
    }

    //end of the level
    if (m_player->isWinner())
    {
        m_win = true;
        m_background.setColor(sf::Color::White);
    }
        
    //colliding gates/rectangle brick
    for (const auto& object : m_static_objects)
    {
        if (!object->isActive())
        {
            object->shutDown();
        }
        object->restart();
    }
}


void Board::createLevel(const GameMaps level, const GameSounds sound)
{
    //level song
    m_game_song.setBuffer(Resources::instance().getGameSounds(sound));
    m_game_song.setLoop(true);
    m_game_song.play();

    //read level board from image by pixel
    const sf::Image& source = Resources::instance().getGameMaps(level);
    for (size_t y = 0; y < source.getSize().y; ++y)
    {
        for (size_t x = 0; x < source.getSize().x; ++x)
        {
            //the object location acording to the pixel location
            const sf::Vector2f location(50 * x + 25, 50 * y + 25);

            //white meens no object
            if (source.getPixel(x, y) == sf::Color::White)
                continue;

            //creating the player sepratly to keep a pointer on him
            else if ((source.getPixel(x, y) == PLAYER_COLOR))
            {
                m_player = new Player(m_world, m_player_textures, location);
                m_moving_objects.push_back(std::unique_ptr<Player>(m_player));
                m_player_location = location;
            }

            //if static object color
            else if (Factory<StaticObject>::isExist(source.getPixel(x, y)))
            {
                m_static_objects.push_back(Factory<StaticObject>::createObject(source.getPixel(x, y),
                    m_world, location));
            }

            //if moving object color
            else if (Factory<MovingObject>::isExist(source.getPixel(x, y)))
            {
                m_moving_objects.push_back(Factory<MovingObject>::createObject(source.getPixel(x, y),
                    m_world, location));
            }
        }
    }
}

const bool Board::isWin() const
{
    return m_win;
}

const int Board::getCoins() const
{
    return m_player->getCoins();
}

void Board::resetBoard()
{
    //clear vectors
    m_static_objects.clear();
    m_moving_objects.clear();
    //reset members
    m_player = nullptr;
    m_win = false;
    m_background.setPosition(0, 0);
    m_background.setColor(sf::Color::White);
    //reset gravity to mormal
    if (m_gravity.y < 0)
        swapGravity();

    // Destroy all fixtures
    b2Body* body = m_world.GetBodyList();
    while (body) {
        b2Fixture* fixture = body->GetFixtureList();
        while (fixture) {
            b2Fixture* nextFixture = fixture->GetNext();
            body->DestroyFixture(fixture);
            fixture = nextFixture;
        }
        body = body->GetNext();
    }

    // Destroy all bodies
    body = m_world.GetBodyList();
    while (body) {
        b2Body* nextBody = body->GetNext();
        m_world.DestroyBody(body);
        body = nextBody;
    }
    //reset song
    m_game_song.pause();
}


