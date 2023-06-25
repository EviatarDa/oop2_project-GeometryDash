#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include "Resources.h"
#include <sstream>


class ScoreTable
{
public:
    ScoreTable(sf::RenderWindow& window);

    void draw()const;
    void saveScoresToFile();
    void addScore(const std::string& scoreText, const int);

private:
    sf::RenderWindow& m_window;
    sf::Font m_font;
    sf::Sprite m_background;
    sf::Text m_title;
    //std::vector< sf::Text> m_scores;
    std::vector<std::pair<int, std::string>> m_scores;
    sf::Vector2f m_table;
    void loadScoresFromFile();
};
