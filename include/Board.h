#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <vector>
#include "Resources.h"
#include "MovingObject.h"
#include "StaticObject.h"
#include "Player.h"
#include "Brick.h"
#include "Coin.h"
#include "Gate.h"
#include "Spike.h"
#include "Jumper.h"
#include "MyContactListener.h"
#include "Enemy.h"

class Board
{
public:
    Board(sf::RenderWindow&, std::pair<GameTextures, GameTextures>);
    void drawBoard();
    void moveObjects();
    b2Vec2 getPlayerPosition();
    void viewBackground(float addition);
    void swapGravity();
    void updateMovingDirections();
    void rightReleased();
    void leftReleased();
    void spaceReleased();
    void changeBoxShip(std::pair<GameTextures, GameTextures>);
    void handleCollision();
    void createLevel(const GameMaps);
    bool isWin();
    int getCoins();


private:
    sf::RenderWindow& m_window;
    b2Vec2 m_gravity;
    b2World m_world;
    std::pair<GameTextures, GameTextures> m_player_textures;

    //game objects:
    std::vector < std::unique_ptr< MovingObject>>  m_moving_objects;
    std::vector < std::unique_ptr< StaticObject>>  m_static_objects;

    sf::Sprite m_background;
    Player* m_player = nullptr;
    sf::Vector2f m_player_location;
    MyContactListener m_contact;
    bool m_win = false;
};