#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string.h>


//window
const int WINDOW_HEIGHT = 800;
const int WINDOW_WIDTH = 1400;

//backgraound
const sf::Color WINDOW_COLOR = sf::Color::Black;


class Resources
{
public:
    Resources();
    ~Resources() = default;
    static Resources& instance();


private:


    void LoadFromFile();

};