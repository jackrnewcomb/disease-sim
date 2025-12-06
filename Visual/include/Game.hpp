
#pragma once
#include "Environment.hpp"
#include <SFML/Graphics.hpp>

class Game
{
  public:
    /**
     * @brief Constructor
     * @param xWin: The number of pixels contained by the window in the X axis
     * @param yWin: The number of pixels contained by the window in the Y axis
     * @param cellSize: The width/height, in pixels, of cells
     */
    Game(int xWin, int yWin, int cellSize);

    /**
     * @brief Performs an update loop for the game. This involves updating sprites with the new Grid information,
     * re-drawing, and re-displaying
     */
    void update();

    /**
     * @brief Returns a bool that describes the current status of the game (running or not running)
     * @returns True if running, false if not
     */
    bool isRunning()
    {
        return isRunning_;
    }

    /**
     * @brief Getter
     * @returns Returns a shared pointer to the Grid
     */
    std::shared_ptr<Environment> getEnvironment()
    {
        return environment_;
    }

  private:
    // A shared pointer to the sf::VideoMode
    std::shared_ptr<sf::VideoMode> vm_;

    // A shared pointer to the sf::RenderWindow
    std::shared_ptr<sf::RenderWindow> window_;

    // A map of textures (allows us to avoid re-loading textures constantly)
    std::map<std::string, sf::Texture> textures_;

    // A shared pointer to the Grid
    std::shared_ptr<Environment> environment_;

    // The height/width of the square cell (total area = cellSize_ * cellSize_)
    int cellSize_;

    // A bool tracking the status of the game (running or not running)
    bool isRunning_{true};
};
