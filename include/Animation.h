#pragma once

#include "Resources.h"
#include "AnimationData.h"
#include <SFML/Graphics.hpp>

class Animation
{
public:
    Animation(const AnimationData&, Direction, sf::Sprite&);
    void direction(Direction dir);
    void update(sf::Time delta);

private:
    const AnimationData& m_data;
    sf::Time m_elapsed = {};
    Direction m_dir = Direction::Right;
    int m_index = 0;
    sf::Sprite& m_sprite;
    void update();
};
