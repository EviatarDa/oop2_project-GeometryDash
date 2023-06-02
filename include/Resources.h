#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string.h>

enum MenuTextures { Menu_Background, Title, Authors };
enum MenuButtons { Play, Help, Box, Score_Table };
enum MenuInstructions { OhNo, Instructions1, DropTheMic };
enum MenuBoxShips { BoxShip1, BoxShip2, BoxShip3, BoxShip4, BoxShip5, BoxShip6 };
enum GameTextures {
    Brick, Level_Background, PlayerBox, PlayerShip, Spike1, Spike2, Spikes, Coin, Cube1, Cube2, CubeCube,
    Gate1, Gate2, Gate3, Gate4, Gate5, Jumper1, Jumper2, Jumper3, Jumper4, Rectangle,
};
enum GameMaps { Map1 };
enum Direction { Up, Down, Right, Left, Stay };

//arrays
const int MENU_TEXTURES = 3;
const int MENU_BUTTONS = 4;
const int MENU_INSTRUCTIONS = 3;
const int MENU_BOX_SHIPS = 6;

const int GAME_TEXTURES = 21;
const int GAME_MAPS = 3;

//window
const int WINDOW_HEIGHT = 800;
const int WINDOW_WIDTH = 1400;

//physics
const float SCALE = 30.f;
const float JUMP_FORCE = 25.f;
const float MOVEMENT_SPEED = 7;

//game object by color
const sf::Color Grey = sf::Color::Color(112, 146, 190);
const sf::Color Red = sf::Color::Color(237, 28, 36);
const sf::Color Cyan = sf::Color::Color(0, 162, 232);
const sf::Color Blue = sf::Color::Color(63, 72, 204);
const sf::Color Yellow = sf::Color::Color(255, 242, 0);
const sf::Color Orange = sf::Color::Color(255, 127, 39);
const sf::Color Black = sf::Color::Black;


class Resources
{
public:
    Resources();
    ~Resources() = default;
    static Resources& instance();

    const sf::Texture& getMenuTexture(const MenuTextures)const;
    const sf::Texture& getMenuButtons(const MenuButtons)const;
    const sf::Texture& getMenuInstructions(const MenuInstructions)const;
    const sf::Texture& getMenuBoxShips(const MenuBoxShips)const;

    const sf::Texture& getGameTexture(const GameTextures)const;

    const sf::Image& getGameMaps(const GameMaps)const;

    const sf::Font& getFont()const;


private:

    sf::Texture m_menu_textures[MENU_TEXTURES];
    sf::Texture m_menu_buttons[MENU_BUTTONS];
    sf::Texture m_menu_instructions[MENU_INSTRUCTIONS];
    sf::Texture m_menu_box_ships[MENU_BOX_SHIPS];

    sf::Texture m_game_textures[GAME_TEXTURES];

    sf::Font m_font;

    sf::Image m_maps[GAME_MAPS];

    void LoadFromFile();

};