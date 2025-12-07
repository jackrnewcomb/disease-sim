#include "Agent.hpp"
#include <random>
#include <vector>

// one "unit" of a map, can be defined as small as you like
class Unit
{
  public:
    Unit()
    {
    }
    Unit(int x, int y)
    {
        xPos = x;
        yPos = y;
    }

    bool SetStartingPopulation()
    {
        // One person, to start
        Agent agent(xPos, yPos);
        population = {agent};
        return true;
    }

    int getPopulationCount()
    {
        return population.size();
    }

    std::vector<Agent> &getPopulation()
    {
        return population;
    }

    bool isInfectious()
    {
        for (auto &agent : population)
        {
            if (agent.getState() == State::Infectious)
                return true;
        }
        return false;
    }

    void AddPerson(Agent &agent)
    {
        population.push_back(agent);
    }

    bool RemovePerson(Agent &agent)
    {
        auto it = std::find_if(population.begin(), population.end(),
                               [&](const Agent &ag) { return &ag == &agent; }); // compare addresses
        if (it != population.end())
        {
            population.erase(it);
            return true;
        }
        return false;
    }

  private:
    std::vector<Agent> population;
    int xPos;
    int yPos;
};
