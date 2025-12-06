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

    State &getState()
    {
        return state;
    }

    void setState(State newState)
    {
        state = newState;
    }

  private:
    int xPos{0};
    int yPos{0};

    State state{State::Susceptible};
};
