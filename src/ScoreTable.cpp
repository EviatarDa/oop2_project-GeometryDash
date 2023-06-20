#include "ScoreTable.h"

ScoreTable::ScoreTable(sf::RenderWindow& window) 
    :m_window(window)
{
    m_background.setTexture(Resources::instance().getGameTexture(Level_Background));
    m_background.scale(1.6, 1.6);

    m_table = (sf::Vector2f(WINDOW_HEIGHT / 2.f, WINDOW_WIDTH / 2.f));

    // Set up title
    m_title.setFont(Resources::instance().getFont());
    m_title.setString("Score Table");
    m_title.setCharacterSize(50);
    m_title.setFillColor(sf::Color::White);
    m_title.setOutlineThickness(2.f);
    m_title.setOutlineColor(sf::Color::Black);
    m_title.setStyle(sf::Text::Bold);
    m_title.setPosition(sf::Vector2f((WINDOW_WIDTH - m_title.getGlobalBounds().width) * 0.5,
        (WINDOW_HEIGHT - m_title.getGlobalBounds().height) * 0.2));

    // Set up scores
    loadScoresFromFile(); // Load scores from file
}

void ScoreTable::draw()
{
    m_window.draw(m_background);
    //m_window.draw(m_table);
    m_window.draw(m_title);
    for (const auto& score : m_scores)
    {
        m_window.draw(score);
    }
}

void ScoreTable::saveScoresToFile()
{
    std::ofstream file("scores.txt");
    if (file.is_open())
    {
        for (const auto& score : m_scores)
        {
            file << score.getString().toAnsiString() << std::endl;
        }
        file.close();
    }

}

void ScoreTable::addScore(const std::string& scoreText)
{
    sf::Text score;
    score.setFont(Resources::instance().getFont());
    score.setString(scoreText);
    score.setCharacterSize(30);
    score.setFillColor(sf::Color::White);
    score.setOutlineColor(sf::Color::Black);
    score.setOutlineThickness(2.f);
    score.setPosition(m_table.x + 20.f, m_scores.size() * 40.f + 250.f);
    m_scores.push_back(score);
}

void ScoreTable::loadScoresFromFile()
{
    std::ifstream file("scores.txt");
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            sf::Text score;
            score.setFont(Resources::instance().getFont());
            score.setString(line);
            score.setCharacterSize(30);
            score.setFillColor(sf::Color::White);
            score.setOutlineColor(sf::Color::Black);
            score.setOutlineThickness(2.f);
            score.setPosition(m_table.x + 20.f, m_scores.size() * 40.f + 100.f);
            m_scores.push_back(score);
        }
        file.close();
    }
}
