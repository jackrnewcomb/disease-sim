#include "Game.hpp"
#include "Environment.hpp"

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

    auto &cells = environment_->getGrid();

    for (int i = 0; i < environment_->getRows(); ++i)
    {
        for (int j = 0; j < environment_->getCols(); ++j)
        {
            int value = cells[environment_->index(i, j)].getPopulationCount();
            float t = std::clamp(value / 10.f, 0.f, 1.f); // normalize
            sf::Uint8 intensity = static_cast<sf::Uint8>(t * 255);
            sf::Color shade;

            auto &unit = environment_->getGrid().at(environment_->index(i, j));

            if (unit.isInfectious())
            {
                // Red tint: full red, reduce green/blue based on population
                shade = sf::Color(intensity, intensity / 2, intensity / 2);
            }
            else
            {
                // Normal grayscale
                shade = sf::Color(intensity, intensity, intensity);
            }

            sf::RectangleShape rect(sf::Vector2f(cellSize_, cellSize_));
            rect.setPosition(static_cast<float>(j * cellSize_), static_cast<float>(i * cellSize_));
            rect.setFillColor(shade);

            window_->draw(rect);
        }
    }

    window_->display();
}
