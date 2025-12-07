#pragma once

#include "State.hpp"
#include <SFML/Graphics.hpp>

struct Heading
{
    int xNext, yNext;
};

class Agent
{
  public:
    Agent(int x, int y) : xPos(x), yPos(y)
    {
    }

    void setHome(int x, int y)
    {
        xHome = x;
        yHome = y;
    }

    void setWorksite(int x, int y)
    {
        xWork = x;
        yWork = y;
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

    bool atHome()
    {
        return xPos == xHome && yPos == yHome;
    }

    bool atWork()
    {
        return xPos == xWork && yPos == yWork;
    }

    std::pair<int, int> nextStep(int x, int y)
    {
        int nextX = xPos;
        int nextY = yPos;

        if (xPos < x)
            nextX++;
        else if (xPos > x)
            nextX--;

        else if (yPos < y)
            nextY++;
        else if (yPos > y)
            nextY--;

        return {nextX, nextY};
    }

    bool goingHome = false;
    bool goingToWork = false;

    int xPos{0}, yPos{0};
    int xHome{0}, yHome{0};
    int xWork{0}, yWork{0};
    State state{State::Susceptible};
};
