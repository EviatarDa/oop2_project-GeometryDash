#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <vector>
#include "Resources.h"

class Board
{
public:
    Board();
    void drawBoard(sf::RenderWindow&);
    void moveObjects();
    void jumpPlayer();
    void movePlayerRight();
    b2Vec2 getPlayerPosition();
    void viewBackground(float addition);


private:
    b2Vec2 m_gravity;
    b2World m_world;
    std::vector<sf::Sprite> m_spikes;
    std::vector<sf::Sprite> m_game_floor;
    std::vector<b2Body*> m_spikes_bodies;
    std::vector<b2Body*> m_floor_bodies;

    sf::Sprite m_background;

    sf::Sprite m_player_box;
    b2Body* m_player_body;

    void createFloor(int, GameTextures);
    void createPlayerBox();
};