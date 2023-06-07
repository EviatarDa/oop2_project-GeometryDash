#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <vector>
#include "Resources.h"
#include "MovingObject.h"
#include "StaticObject.h"
#include "Player.h"
#include "Brick.h"

class Board
{
public:
    Board(sf::RenderWindow&, std::pair<GameTextures, GameTextures>);
    ~Board();
    void drawBoard();
    void moveObjects();
    b2Vec2 getPlayerPosition();
    void viewBackground(float addition);
    void swapGravity();
    void updateMovingDirections();
    void changeBoxShip(std::pair<GameTextures, GameTextures>);


private:
    sf::RenderWindow& m_window;
    b2Vec2 m_gravity;
    b2World m_world;
    std::pair<GameTextures, GameTextures> m_player_textures;

    //game objects:
    std::vector < std::unique_ptr< MovingObject>>  m_moving_objects;
    std::vector < std::unique_ptr< StaticObject>>  m_static_objects;

    std::vector<sf::Sprite> m_game_floor;
    std::vector<b2Body*> m_floor_bodies;

    sf::Sprite m_background;

    void createLevel();
    //void createPhysicalBody(const sf::Sprite&, const sf::Vector2u);
    //std::pair<sf::Sprite, sf::Vector2u> createSprite( const int,  const int,  const GameTextures);
};