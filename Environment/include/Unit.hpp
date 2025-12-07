#pragma once
#include "Agent.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <vector>

// one "unit" of a map, can be defined as small as you like
class Unit
{
  public:
    Unit() = delete;

    Unit(int x, int y) : xPos(x), yPos(y)
    {
    }

    bool SetStartingPopulation()
    {
        // One person, to start
        auto agent = std::make_shared<Agent>(xPos, yPos);
        population = {agent};
        return true;
    }

    size_t getPopulationCount()
    {
        return population.size();
    }

    std::vector<std::shared_ptr<Agent>> &getPopulation()
    {
        return population;
    }

    bool isInfectious()
    {
        for (auto &agent : population)
        {
            if (agent->getState() == State::Infectious)
                return true;
        }
        return false;
    }

    void AddPerson(std::shared_ptr<Agent> agent)
    {
        population.push_back(agent);
        agent->setPosition(xPos, yPos);
    }

    void RemovePerson(std::shared_ptr<Agent> agent)
    {
        population.erase(std::remove(population.begin(), population.end(), agent), population.end());
    }

    sf::Color getBaseColor() const
    {
        return color;
    }

  protected:
    std::vector<std::shared_ptr<Agent>> population;
    int xPos{0};
    int yPos{0};
    sf::Color color = sf::Color::White;
};
