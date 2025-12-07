#include "Environment.hpp"
#include "Home.hpp"
#include "SocialHub.hpp"
#include "Worksite.hpp"

Environment::Environment(int xLen, int yLen)
{
    // Initialize row/column members
    rows_ = xLen;
    cols_ = yLen;

    // Set the size of cells_ and newGrid_ to be the correct size of the grid
    grid_.resize(rows_ * cols_);
    newGrid_.resize(rows_ * cols_);

    for (int i = 0; i < rows_; ++i)
    {
        for (int j = 0; j < cols_; ++j)
        {
            Unit unit;
            if (i % 7 == 0 && j % 7 == 0)
                unit = Home(i, j);
            else
            {
                unit = Unit(i, j);
            }
            // else if ((i + j) % 10 == 0)
            //     unit = std::make_shared<SocialHub>(i, j);
            // else
            //     unit = std::make_shared<Home>(i, j);
            unit.SetStartingPopulation();
            grid_.at(index(i, j)) = unit;
        }
    }

    // testing, set 1 guy to be infectious
    grid_.at(index(0, 0)).getPopulation().at(0).setState(State::Infectious);

    newGrid_ = grid_;
}

void Environment::update()
{
    // Reset newGrid_ to empty units with correct positions
    // for (int i = 0; i < rows_; ++i)
    //{
    //    for (int j = 0; j < cols_; ++j)
    //    {
    //        newGrid_[index(i, j)] = std::make_unique<Unit>(i, j);
    //    }
    //}
    // ??????????????

    // Process movements
    for (int i = 0; i < rows_; ++i)
    {
        for (int j = 0; j < cols_; ++j)
        {
            updateUnit(i, j);
        }
    }

    // Swap content so grid_ now holds the updated data
    grid_.swap(newGrid_);
}

void Environment::updateUnit(int i, int j)
{
    auto &unit = grid_.at(index(i, j));
    auto &pop = unit.getPopulation();

    bool infectiousUnit = false;
    for (auto &agent : pop)
    {
        if (agent.getState() == State::Infectious)
        {
            infectiousUnit = true;
        }
    }

    for (int k = pop.size() - 1; k >= 0; --k)
    {
        Agent &agent = pop[k];

        if (infectiousUnit)
        {
            agent.setState(State::Infectious);
        }

        std::vector<std::pair<int, int>> possibleMoves;
        for (int iDelta = -1; iDelta <= 1; ++iDelta)
        {
            for (int jDelta = -1; jDelta <= 1; ++jDelta)
            {
                if (iDelta == 0 && jDelta == 0)
                    continue;
                int ni = i + iDelta;
                int nj = j + jDelta;
                if (ni >= 0 && ni < rows_ && nj >= 0 && nj < cols_)
                    possibleMoves.push_back({ni, nj});
            }
        }

        int choice = 0;
        if (!possibleMoves.empty())
        {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, possibleMoves.size() - 1);
            choice = dis(gen);
        }

        int newI = possibleMoves[choice].first;
        int newJ = possibleMoves[choice].second;

        // Move agent to new unit
        newGrid_[index(newI, newJ)].AddPerson(agent);

        // Remove agent from old unit (not strictly necessary here, since old grid is discarded)
        pop.erase(pop.begin() + k);
    }
}
