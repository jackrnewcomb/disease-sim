#pragma once
#include "Agent.hpp"
#include "Unit.hpp"
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

class SocialHub : public Unit
{
  public:
    SocialHub(int x, int y) : Unit(x, y)
    {
    }

  private:
    std::vector<Agent> regulars;
};
