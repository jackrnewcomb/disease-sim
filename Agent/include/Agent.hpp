#pragma once

#include "State.hpp"
#include <SFML/Graphics.hpp>

class Agent
{
  public:
    Agent(int x, int y) : xPos(x), yPos(y), xHome(x), yHome(y)
    {
    }

    State &getState()
    {
        return state;
    }

    void setState(State newState)
    {
        state = newState;
    }

    void setPosition(int x, int y)
    {
        xPos = x;
        yPos = y;
    }

  private:
    int xPos, yPos;
    int xHome, yHome;
    State state{State::Susceptible};
};
