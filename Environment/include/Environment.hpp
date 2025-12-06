#pragma once
#include "Agent.hpp"
#include <vector>

// one "unit" of a map, can be defined as small as you like
class Unit
{
  public:
    Unit()
    {
    }

  private:
    std::vector<Agent> population;
};

class Environment
{

  public:
    Environment()
    {
    }

    bool Update()
    {
        return true;
    }

  private:
    std::vector<std::vector<Unit>> grid;
    int day{0};
};
