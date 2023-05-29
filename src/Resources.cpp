#pragma once

#include "Resources.h"

Resources::Resources()
{
	LoadFromFile();
}

Resources& Resources::instance()
{
	static Resources Resource;
	return Resource;
}

const sf::Texture& Resources::getMenuTexture(const MenuTextures texture) const
{
	return m_menu_textures[texture];
}

const sf::Texture& Resources::getMenuButtons(const MenuButtons button) const
{
	return m_menu_buttons[button];
}

const sf::Font& Resources::getFont() const
{
	return m_font;
}


void Resources::LoadFromFile()
{
	//menu textures
	m_menu_textures[Menu_Backgound].loadFromFile("Menu_Backgound.png");
	m_menu_textures[Menu_Backgound].setSmooth(true);
	m_menu_textures[Title].loadFromFile("Title.png");
	m_menu_textures[Title].setSmooth(true);
	m_menu_textures[Authors].loadFromFile("Authors.png");

	m_menu_buttons[Play].loadFromFile("Play.png");
	m_menu_buttons[Help].loadFromFile("Help.png");
	m_menu_buttons[Box].loadFromFile("Box.png");
	m_menu_buttons[Score_Table].loadFromFile("Score_Table.png");

	m_font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
}

