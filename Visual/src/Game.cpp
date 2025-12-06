#include "Game.hpp"
#include "Environment.hpp"

Game::Game(int xWin, int yWin, int cellSize)
{
    // Initialize members
    vm_ = std::make_shared<sf::VideoMode>(xWin, yWin);
    window_ = std::make_shared<sf::RenderWindow>(*vm_, "sim", sf::Style::Default);
    cellSize_ = cellSize;
    environment_ = std::make_shared<Environment>(xWin / cellSize, yWin / cellSize);

    // Populate the textures_ map so we only have to load textures once
    textures_["dead"].loadFromFile("graphics/dead.png");
    textures_["alive"].loadFromFile("graphics/alive.png");
}

void Game::update()
{
    // If the user presses escape, close the window
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        isRunning_ = false;
        window_->close();
    }

    // Redraw the map with new movements and entity updates
    window_->clear();

    // Get the cells from our grid
    auto &cells = environment_->getGrid();

    // For each row and column in the grid...
    for (int i = 0; i < environment_->getRows(); i++)
    {
        for (int j = 0; j < environment_->getCols(); j++)
        {
            // Make a sprite
            sf::Sprite sprite;

            auto value = cells[environment_->index(i, j)].getPopulation(); // some integer value

            // Normalize to [0,255] depending on your maximum possible value
            int maxValue = 10; // whatever your max is
            float t = std::clamp(value / float(maxValue), 0.f, 1.f);

            sf::Color shade(static_cast<sf::Uint8>(t * 255), static_cast<sf::Uint8>(t * 255),
                            static_cast<sf::Uint8>(t * 255));

            sprite.setTexture(textures_["cell"]);
            sprite.setColor(shade);

            // Set the position to be the location of the row and column, factoring in cell size
            sprite.setPosition(static_cast<float>(i * cellSize_), static_cast<float>(j * cellSize_));

            // Set the scale dependent on cell size and texture size
            sprite.setScale(cellSize_ / static_cast<float>(sprite.getTexture()->getSize().x),
                            cellSize_ / static_cast<float>(sprite.getTexture()->getSize().y));

            // Draw the sprite
            window_->draw(sprite);
        }
    }

    // Display after drawing all sprites
    window_->display();
}
