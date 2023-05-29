#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include "Resources.h"


class ScoreTable
{
public:
    ScoreTable(sf::RenderWindow& window);

    void draw();
    void saveScoresToFile();
    void addScore(const std::string& scoreText);

private:
    sf::RenderWindow& m_window;
    sf::Font m_font;
    sf::RectangleShape m_table;
    sf::Text m_title;
    std::vector<sf::Text> m_scores;

    void loadScoresFromFile();
};
