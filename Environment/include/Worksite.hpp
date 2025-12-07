#pragma once
#include "Agent.hpp"
#include "Unit.hpp"
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

class Worksite : public Unit
{
  public:
    Worksite()
    {
    }

  private:
    std::vector<Agent> workers;
};
