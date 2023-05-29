#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string.h>

enum MenuTextures { Menu_Backgound, Title, Authors };
enum MenuButtons{ Play, Help, Box, Score_Table };

//window
const int WINDOW_HEIGHT = 800;
const int WINDOW_WIDTH = 1400;

//backgraound
const sf::Color WINDOW_COLOR = sf::Color::Black;

const int MENU_TEXTURES = 3;
const int MENU_BUTTONS = 4;

class Resources
{
public:
    Resources();
    ~Resources() = default;
    static Resources& instance();

    const sf::Texture& getMenuTexture(const MenuTextures)const;
    const sf::Texture& getMenuButtons(const MenuButtons)const;
    const sf::Font& getFont()const;


private:

    sf::Texture m_menu_textures[MENU_TEXTURES];
    sf::Texture m_menu_buttons[MENU_BUTTONS];

    sf::Font m_font;

    void LoadFromFile();

};