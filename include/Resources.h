#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string.h>
#include <unordered_map>


enum MenuTextures { Menu_Background, Title };
enum MenuButtons { Play, Help, Box, Score_Table, WithoutYou, Greyhound, OnlyTheHorses, Spectre };
enum MenuInstructions { OhNo, Instructions1, Instructions2, Instructions3, DropTheMic };
enum MenuBoxShips { BoxShip1, BoxShip2, BoxShip3, BoxShip4, BoxShip5, BoxShip6 };
enum GameTextures {
    Floor, Level_Background, PlayerBox1, PlayerBox2, PlayerBox3, PlayerBox4, PlayerBox5, PlayerBox6,
    PlayerShip1, PlayerShip2, PlayerShip3, PlayerShip4, PlayerShip5, PlayerShip6, Spike1, Spike2, Spikes,
    Coin, Cube1, Cube2, CubeCube, Gate1, Gate2, Gate3, Gate4, Gate5, Jumper1, Jumper2, Rectangle,
    Enemy1SpriteSheet, Enemy2SpriteSheet, Enemy1, Enemy2
};
enum GameMaps { Map1, Map2, Map3, Map4 };
enum Direction { Right, Left, Up, Stay };
enum GameAnimations { Enemy1Animation, Enemy2Animation };

//arrays
const int MENU_TEXTURES = 2;
const int MENU_BUTTONS = 9;
const int MENU_INSTRUCTIONS = 5;
const int MENU_BOX_SHIPS = 6;

const int GAME_TEXTURES = 33;
const int GAME_MAPS = 4;

const int GAME_ANIMATIONS = 2;

//window
const int WINDOW_HEIGHT = 800;
const int WINDOW_WIDTH = 1400;

//physics
const float SCALE = 30.f;
const float BOX_JUMP_FORCE = 25.f;
const float BOX_HOP_FORCE = 50.f;
const float SHIP_JUMP_FORCE = 5.f;
const float PLAYER_MOVEMENT_SPEED = 7;
const float ENEMY_MOVEMENT_SPEED = 3;


//game object by color
const sf::Color FLOOR_COLOR = sf::Color::Black;
const sf::Color CUBE_CUBE_COLOR = sf::Color(112, 146, 190);
const sf::Color SPIKE1_COLOR = sf::Color(237, 28, 36);
const sf::Color SPIKE1_UP_COLOR = sf::Color(239, 228, 176);
const sf::Color CUBE2_COLOR = sf::Color(0, 162, 232);
const sf::Color CUBE1_COLOR = sf::Color(63, 72, 204);
const sf::Color COIN_COLOR = sf::Color(255, 242, 0);
const sf::Color GATE1_COLOR = sf::Color(255, 127, 39);
const sf::Color GATE2_COLOR = sf::Color(163, 73, 164);
const sf::Color GATE3_COLOR = sf::Color(200, 191, 231);
const sf::Color GATE4_COLOR = sf::Color(136, 0, 21);
const sf::Color GATE5_COLOR = sf::Color(64, 128, 128);
const sf::Color RECTANGLE_COLOR = sf::Color(153, 217, 234);
const sf::Color SPIKES_COLOR = sf::Color(255, 174, 201);
const sf::Color SPIKE2_COLOR = sf::Color(185, 122, 87);
const sf::Color JUMPER2_COLOR = sf::Color(34, 177, 76);
const sf::Color JUMPER1_COLOR = sf::Color(181, 230, 29);
const sf::Color JUMPER1_UP_COLOR = sf::Color(127, 127, 127);
const sf::Color PLAYER_COLOR = sf::Color(255, 201, 14);
const sf::Color ENEMY1_COLOR = sf::Color(195, 195, 195);
const sf::Color ENEMY1_UP_COLOR = sf::Color(117, 22, 63);
const sf::Color ENEMY2_COLOR = sf::Color(234, 54, 128);
const sf::Color ENEMY2_UP_COLOR = sf::Color(120, 67, 21);

struct AnimationData
{
    using ListType = std::vector<sf::IntRect>;
    using DataType = std::unordered_map<Direction, ListType>;
    DataType m_data;
};


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

    const AnimationData& getAnimationData(GameAnimations)const;


private:

    sf::Texture m_menu_textures[MENU_TEXTURES];
    sf::Texture m_menu_buttons[MENU_BUTTONS];
    sf::Texture m_menu_instructions[MENU_INSTRUCTIONS];
    sf::Texture m_menu_box_ships[MENU_BOX_SHIPS];
    
    sf::Texture m_game_textures[GAME_TEXTURES];

    sf::Font m_font;

    sf::Image m_maps[GAME_MAPS];

    std::vector<AnimationData> m_animation_data;

    void LoadFromFile();

};