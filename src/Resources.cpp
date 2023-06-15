#pragma once

#include "Resources.h"


namespace
{
	AnimationData enemyData()
	{
		const auto size = sf::Vector2i(53, 50);
		const auto initSpace = sf::Vector2i(0, 0);
		const auto middleSpace = sf::Vector2i(0, 0);

		auto enemy = AnimationData{};
		auto currentStart = initSpace;

		auto nextStart = [&]()
		{
			currentStart += middleSpace;
			currentStart.x += size.x;
			return currentStart;
		};

		enemy.m_data[Right].emplace_back(currentStart, size);
		enemy.m_data[Right].emplace_back(nextStart(), size);
		enemy.m_data[Right].emplace_back(nextStart(), size);
		enemy.m_data[Right].emplace_back(nextStart(), size);
		enemy.m_data[Right].emplace_back(nextStart(), size);
		enemy.m_data[Right].emplace_back(nextStart(), size);
		enemy.m_data[Right].emplace_back(nextStart(), size);
		enemy.m_data[Right].emplace_back(nextStart(), size);
		enemy.m_data[Right].emplace_back(nextStart(), size);
		enemy.m_data[Right].emplace_back(nextStart(), size);

		enemy.m_data[Left].emplace_back(nextStart(), size);
		enemy.m_data[Left].emplace_back(nextStart(), size);
		enemy.m_data[Left].emplace_back(nextStart(), size);
		enemy.m_data[Left].emplace_back(nextStart(), size);
		enemy.m_data[Left].emplace_back(nextStart(), size);
		enemy.m_data[Left].emplace_back(nextStart(), size);
		enemy.m_data[Left].emplace_back(nextStart(), size);
		enemy.m_data[Left].emplace_back(nextStart(), size);
		enemy.m_data[Left].emplace_back(nextStart(), size);
		enemy.m_data[Left].emplace_back(nextStart(), size);

		return enemy;
	}
}


Resources::Resources()
	:m_animation_data(GAME_ANIMATIONS)
{
	LoadFromFile();
	m_animation_data[EnemyAnimation] = enemyData();
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

const sf::Texture& Resources::getMenuInstructions(const MenuInstructions page) const
{
	return m_menu_instructions[page];
}

const sf::Texture& Resources::getMenuBoxShips(const MenuBoxShips box_ship) const
{
	return m_menu_box_ships[box_ship];
}

const sf::Texture& Resources::getGameTexture(const GameTextures texture) const
{
	return m_game_textures[texture];
}

const sf::Image& Resources::getGameMaps(const GameMaps map) const
{
	return m_maps[map];
}

const sf::Font& Resources::getFont() const
{
	return m_font;
}

const AnimationData& Resources::getAnimationData(GameAnimations animation) const
{
	return m_animation_data[animation];
}


void Resources::LoadFromFile()
{
	//menu textures
	m_menu_textures[Menu_Background].loadFromFile("Menu_Backgound.png");
	m_menu_textures[Menu_Background].setSmooth(true);
	m_menu_textures[Title].loadFromFile("Title.png");
	m_menu_textures[Title].setSmooth(true);
	m_menu_textures[Authors].loadFromFile("Authors.png");

	m_menu_buttons[Play].loadFromFile("Play.png");
	m_menu_buttons[Help].loadFromFile("Help.png");
	m_menu_buttons[Box].loadFromFile("Box.png");
	m_menu_buttons[Score_Table].loadFromFile("Score_Table.png");

	m_menu_instructions[OhNo].loadFromFile("OhNo.png");
	m_menu_instructions[Instructions1].loadFromFile("Instructions1.png");
	m_menu_instructions[DropTheMic].loadFromFile("DropTheMic.png");

	m_menu_box_ships[BoxShip1].loadFromFile("BoxShip1.png");
	m_menu_box_ships[BoxShip2].loadFromFile("BoxShip2.png");
	m_menu_box_ships[BoxShip3].loadFromFile("BoxShip3.png");
	m_menu_box_ships[BoxShip4].loadFromFile("BoxShip4.png");
	m_menu_box_ships[BoxShip5].loadFromFile("BoxShip5.png");
	m_menu_box_ships[BoxShip6].loadFromFile("BoxShip6.png");


	//game textures
	m_game_textures[Floor].loadFromFile("Floor.png");
	m_game_textures[Level_Background].loadFromFile("Menu_Backgound.png");
	m_game_textures[PlayerBox1].loadFromFile("PlayerBox1.png");
	m_game_textures[PlayerBox2].loadFromFile("PlayerBox2.png");
	m_game_textures[PlayerBox3].loadFromFile("PlayerBox3.png");
	m_game_textures[PlayerBox4].loadFromFile("PlayerBox4.png");
	m_game_textures[PlayerBox5].loadFromFile("PlayerBox5.png");
	m_game_textures[PlayerBox6].loadFromFile("PlayerBox6.png");
	m_game_textures[PlayerShip1].loadFromFile("PlayerShip1.png");
	m_game_textures[PlayerShip2].loadFromFile("PlayerShip2.png");
	m_game_textures[PlayerShip3].loadFromFile("PlayerShip3.png");
	m_game_textures[PlayerShip4].loadFromFile("PlayerShip4.png");
	m_game_textures[PlayerShip5].loadFromFile("PlayerShip5.png");
	m_game_textures[PlayerShip6].loadFromFile("PlayerShip6.png");
	m_game_textures[Spike1].loadFromFile("Spike1.png");
	m_game_textures[Spike2].loadFromFile("Spike2.png");
	m_game_textures[Spikes].loadFromFile("Spikes.png");
	m_game_textures[Coin].loadFromFile("Coin.png");
	m_game_textures[Cube1].loadFromFile("Cube1.png");
	m_game_textures[Cube2].loadFromFile("Cube2.png");
	m_game_textures[CubeCube].loadFromFile("CubeCube.png");
	m_game_textures[Gate1].loadFromFile("Gate1.png");
	m_game_textures[Gate2].loadFromFile("Gate2.png");
	m_game_textures[Gate3].loadFromFile("Gate3.png");
	m_game_textures[Gate4].loadFromFile("Gate4.png");
	m_game_textures[Gate5].loadFromFile("Gate5.png");
	m_game_textures[Jumper1].loadFromFile("Jumper1.png");
	m_game_textures[Jumper2].loadFromFile("Jumper2.png");
	m_game_textures[Jumper3].loadFromFile("Jumper3.png");
	m_game_textures[Jumper4].loadFromFile("Jumper4.png");
	m_game_textures[Rectangle].loadFromFile("Rectangle.png");
	m_game_textures[EnemySpriteSheet].loadFromFile("Enemy2SpriteSheet.png");

	//game image
	m_maps[Map1].loadFromFile("Map.png");

	//font
	m_font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
}

