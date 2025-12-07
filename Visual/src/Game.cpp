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

            //
            // 1. Draw the UNIT background color
            //
            sf::RectangleShape cell(sf::Vector2f(cellSize_, cellSize_));
            cell.setPosition(j * cellSize_, i * cellSize_);
            cell.setFillColor(unit.getBaseColor());
            window_->draw(cell);

            //
            // 2. Draw AGENT DOTS on top
            //
            for (auto &agent : unit.getPopulation())
            {
                sf::CircleShape dot(cellSize_ * 0.25f);
                dot.setOrigin(dot.getRadius(), dot.getRadius());

                dot.setPosition(j * cellSize_ + cellSize_ * 0.5f, i * cellSize_ + cellSize_ * 0.5f);

                if (agent->getState() == State::Infectious)
                    dot.setFillColor(sf::Color(255, 80, 80));
                else
                    dot.setFillColor(sf::Color(230, 230, 230));

                window_->draw(dot);
            }
        }
    }

    window_->display();
}
