#pragma once

#include "State.hpp"

class Agent
{

  public:
    Agent()
    {
    }

  private:
    double xPos{0.0};
    double yPos{0.0};

    State state{State::Susceptible};
};
