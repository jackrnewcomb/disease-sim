#pragma once
#include "Agent.hpp"
#include "Unit.hpp"
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

class Worksite : public Unit
{
  public:
    Worksite(int x, int y) : Unit(x, y)
    {
        color = sf::Color(180, 180, 255);
    }

  private:
    std::vector<Agent> workers;
};
