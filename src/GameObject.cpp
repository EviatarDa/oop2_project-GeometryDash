#pragma once

#include "GameObject.h"

GameObject::GameObject(const GameTextures texture, const sf::Vector2f location)
    :m_object_body(nullptr)
{
    m_object.setTexture(Resources::instance().getGameTexture(texture));
    sf::Vector2f sprite_size(m_object.getTextureRect().width, m_object.getTextureRect().height);
    m_object.setOrigin(sprite_size.x / 2, sprite_size.y / 2);
    m_object.setPosition(location);
}


GameObject::~GameObject()
{
    m_object_body = nullptr;
}

void GameObject::draw(sf::RenderWindow& window) const
{
    window.draw(m_object);
}

const b2Body* GameObject::getBody() const
{
    return m_object_body;
}
