#pragma once

#include "State.hpp"

class Agent
{

  public:
    Agent() = delete;
    Agent(int x, int y)
    {
        xPos = x;
        yPos = y;
    }

  private:
    int xPos{0};
    int yPos{0};

    State state{State::Susceptible};
};
