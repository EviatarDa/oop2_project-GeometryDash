#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string.h>

enum MenuTextures { Menu_Background, Title, Authors };
enum MenuButtons{ Play, Help, Box, Score_Table };
enum GameTextures{ Floor, Level_Background, PlayerBox};

//window
const int WINDOW_HEIGHT = 800;
const int WINDOW_WIDTH = 1400;

//backgraound
const sf::Color WINDOW_COLOR = sf::Color::Black;

const float SCALE = 30.f;
const float JUMP_FORCE = 900.f;
const float MOVEMENT_FORCE = 1000.f;

const float MAX_JUMP_HEIGHT = 800.0f;
const float MAX_MOVEMENT_SPEED = 300.0f;


const int MENU_TEXTURES = 3;
const int MENU_BUTTONS = 4;
const int GAME_TEXTURES = 3;

class Resources
{
public:
    Resources();
    ~Resources() = default;
    static Resources& instance();

    const sf::Texture& getMenuTexture(const MenuTextures)const;
    const sf::Texture& getMenuButtons(const MenuButtons)const;

    const sf::Texture& getGameTexture(const GameTextures)const;

    const sf::Font& getFont()const;


private:

    sf::Texture m_menu_textures[MENU_TEXTURES];
    sf::Texture m_menu_buttons[MENU_BUTTONS];

    sf::Texture m_game_textures[GAME_TEXTURES];

    sf::Font m_font;

    void LoadFromFile();

};