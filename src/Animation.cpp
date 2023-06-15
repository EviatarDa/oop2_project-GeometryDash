#pragma once

#include "Animation.h"

const auto AnimationTime = sf::seconds(0.07f);

Animation::Animation(const AnimationData& data, Direction dir, sf::Sprite& sprite, GameTextures sprite_sheet)
    : m_data(data), m_dir(dir), m_sprite(sprite)
{
    m_sprite.setTexture(Resources::instance().getGameTexture(sprite_sheet));
    update();
}

void Animation::direction(Direction dir)
{
    if (m_dir == dir || dir == Direction::Stay)
    {
        return;
    }

    m_dir = dir;
    update();
}

void Animation::update(sf::Time delta)
{
    m_elapsed += delta;
    if (m_elapsed >= AnimationTime)
    {
        m_elapsed -= AnimationTime;
        ++m_index;
        m_index %= m_data.m_data.find(m_dir)->second.size();
        update();
    }
}

void Animation::update()
{
    m_sprite.setTextureRect(m_data.m_data.find(m_dir)->second[m_index]);
}
