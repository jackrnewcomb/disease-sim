#pragma once
#include "Agent.hpp"
#include "Unit.hpp"
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

class Home : public Unit
{
  public:
    Home(int x, int y) : Unit(x, y)
    {
        color = sf::Color(180, 255, 180);
    }

  protected:
    std::vector<Agent> householdMembers;
};
