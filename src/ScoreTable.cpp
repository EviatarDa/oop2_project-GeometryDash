#include "ScoreTable.h"

ScoreTable::ScoreTable(sf::RenderWindow& window) : m_window(window)
{
    

    // Set up table properties
    m_table.setSize(sf::Vector2f(400.f, 300.f));
    m_table.setPosition(m_window.getSize().x / 2.f - m_table.getSize().x / 2.f,
        m_window.getSize().y / 2.f - m_table.getSize().y / 2.f);
    m_table.setFillColor(sf::Color::White);
    m_table.setOutlineColor(sf::Color::Black);
    m_table.setOutlineThickness(2.f);

    // Set up title
    m_title.setFont(Resources::instance().getFont());
    m_title.setString("Score Table");
    m_title.setCharacterSize(24);
    m_title.setFillColor(sf::Color::Black);
    m_title.setStyle(sf::Text::Bold);
    m_title.setPosition(m_table.getPosition().x + m_table.getSize().x / 2.f - m_title.getLocalBounds().width / 2.f,
        m_table.getPosition().y + 20.f);

    // Set up scores
    loadScoresFromFile(); // Load scores from file
}

void ScoreTable::draw()
{
    m_window.draw(m_table);
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
    score.setCharacterSize(18);
    score.setFillColor(sf::Color::Black);
    score.setPosition(m_table.getPosition().x + 20.f, m_scores.size() * 30.f + 100.f);
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
            score.setCharacterSize(18);
            score.setFillColor(sf::Color::Black);
            score.setPosition(m_table.getPosition().x + 20.f, m_scores.size() * 30.f + 100.f);
            m_scores.push_back(score);
        }
        file.close();
    }
}
