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

void ScoreTable::draw()const
{
    m_window.draw(m_background);
    m_window.draw(m_title);
    for (int index = 0 ; index < m_scores.size(); index++)
    {
        sf::Text text;
        text.setFont(Resources::instance().getFont());
        text.setString(m_scores[index].second + "   " + std::to_string(m_scores[index].first));
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::White);
        text.setOutlineColor(sf::Color::Black);
        text.setOutlineThickness(2.f);
        text.setPosition(m_table.x + 20.f, index * 40.f + 250.f);
        m_window.draw(text);
    }
}

void ScoreTable::saveScoresToFile()
{
    std::ofstream file("scores.txt");
    if (file.is_open())
    {
        for (const auto& score : m_scores)
        {
            file << score.first << " " << score.second << "\n";
        }
        file.close();
    }
}

void ScoreTable::addScore(const std::string& name, const int score)
{
    m_scores.push_back(std::pair<int, std::string>(score, name));
    std::sort(m_scores.begin(), m_scores.end(),
        [](const std::pair<int, std::string>& obj1, const std::pair<int, std::string>& obj2) {return obj1.first > obj2.first; });

    if (m_scores.size() > 10)
    {
        m_scores.pop_back();
    }
}

void ScoreTable::loadScoresFromFile()
{
    std::ifstream file("scores.txt");
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::stringstream ss(line);
            int number = 0;
            std::string name;
            ss >> number;
            std::getline(ss,name);
            m_scores.push_back(std::pair<int, std::string>(number, name));
        }
        file.close();
    }
    else
        throw std::invalid_argument("cannot open scores.txt file");
}
