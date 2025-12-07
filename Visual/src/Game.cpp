#include "Game.hpp"
#include "Environment.hpp"
#include "Home.hpp"

Game::Game(int xWin, int yWin, int cellSize)
{
    // Initialize members
    vm_ = std::make_shared<sf::VideoMode>(xWin, yWin);
    window_ = std::make_shared<sf::RenderWindow>(*vm_, "sim", sf::Style::Default);
    cellSize_ = cellSize;
    environment_ = std::make_shared<Environment>(xWin / cellSize, yWin / cellSize);
}

void Game::update()
{
    // If the user presses escape, close the window
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        isRunning_ = false;
        window_->close();
    }

    window_->clear();

    for (int i = 0; i < environment_->getRows(); ++i)
    {
        for (int j = 0; j < environment_->getCols(); ++j)
        {
            Unit &unit = environment_->getGrid().at(environment_->index(i, j));

            auto popCount = unit.getPopulationCount();
            float popFactor = std::clamp(popCount / 10.f, 0.f, 1.f); // normalize for brightness

            // Determine base color depending on derived class
            auto color = unit.getBaseColor();

            // Scale brightness by population
            sf::Color shade(static_cast<sf::Uint8>(color.r * popFactor), static_cast<sf::Uint8>(color.g * popFactor),
                            static_cast<sf::Uint8>(color.b * popFactor));

            // Overlay red if there are infectious people
            if (unit.isInfectious())
            {
                shade.r = std::max(shade.r, static_cast<sf::Uint8>(200)); // boost red
                shade.g = static_cast<sf::Uint8>(shade.g * 0.5f);
                shade.b = static_cast<sf::Uint8>(shade.b * 0.5f);
            }

            sf::RectangleShape rect(sf::Vector2f(cellSize_, cellSize_));
            rect.setPosition(static_cast<float>(j * cellSize_), static_cast<float>(i * cellSize_));
            rect.setFillColor(shade);

            window_->draw(rect);
        }
    }

    window_->display();
}
