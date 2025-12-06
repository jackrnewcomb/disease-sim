#pragma once
#include "Agent.hpp"
#include <random>
#include <vector>

// one "unit" of a map, can be defined as small as you like
class Unit
{
  public:
    Unit()
    {
    }
    Unit(int x, int y)
    {
        xPos = x;
        yPos = y;
    }

    bool SetStartingPopulation()
    {
        // One person, to start
        Agent agent(xPos, yPos);
        population = {agent};
        return true;
    }

    int getPopulationCount()
    {
        return population.size();
    }

    std::vector<Agent> getPopulation()
    {
        return population;
    }

    void AddPerson(Agent &agent)
    {
        population.push_back(agent);
    }

    bool RemovePerson(Agent &agent)
    {
        auto it = std::find_if(population.begin(), population.end(),
                               [&](const Agent &ag) { return &ag == &agent; }); // compare addresses
        if (it != population.end())
        {
            population.erase(it);
            return true;
        }
        return false;
    }

  private:
    std::vector<Agent> population;
    int xPos;
    int yPos;
};

class Environment
{

  public:
    Environment(int xLen, int yLen);

    void update();

    void updateUnit(int i, int j);

    std::vector<Unit> &getGrid()
    {
        return grid_;
    }

    /**
     * @brief Getter
     * @returns Returns the number of rows
     */
    int getRows()
    {
        return rows_;
    }

    /**
     * @brief Getter
     * @returns Returns the number of columns
     */
    int getCols()
    {
        return cols_;
    }

    /**
     * @brief An indexer. Since we're using a flattened, 1D vector to store cell status, this takes in a row and column
     * and provides the actual index of the cells_ vector
     * @param i: The desired row
     * @param j: The desired column
     * @returns Index given row and column
     */
    int index(int i, int j)
    {
        return i * cols_ + j;
    }

    bool Update()
    {
        day++;
        return true;
    }

    int getDay()
    {
        return day;
    }

  private:
    int day{0};

    // The number of rows in the grid
    int rows_;

    // The number of columns in the grid
    int cols_;

    // The flattened 1D vector of cells
    std::vector<Unit> grid_;

    // The "next" vector after the update (required to avoid overlapping cell statuses)
    std::vector<Unit> newCells_;

    // Random Number Generator
    std::default_random_engine generator;
};
