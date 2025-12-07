#include "Environment.hpp"
#include "Home.hpp"
#include "SocialHub.hpp"
#include "Worksite.hpp"

Environment::Environment(int xLen, int yLen)
{

    // Initialize row/column members
    rows_ = xLen;
    cols_ = yLen;

    grid_.reserve(rows_ * cols_); // pre-allocate memory
    for (int i = 0; i < rows_; ++i)
    {
        for (int j = 0; j < cols_; ++j)
        {
            if (i == 5 && j == 5)
                grid_.emplace_back(Home(i, j));
            else if (i == 25 && j == 25)
                grid_.emplace_back(Worksite(i, j));
            else
                grid_.emplace_back(Unit(i, j));
        }
    }

    // testing, set 1 guy to be infectious
    // grid_.at(index(0, 0)).getPopulation().at(0).setState(State::Infectious);

    // testing, add 1 guy
    grid_.at(index(5, 5)).SetStartingPopulation();
    grid_.at(index(5, 5)).getPopulation().at(0)->setState(State::Infectious);
}

struct Move
{
    std::shared_ptr<Agent> agent;
    int fromI, fromJ;
    int toI, toJ;
};

void Environment::update()
{
    std::vector<Move> moves;
    moves.reserve(1024);

    // decide moves for every cell exactly once
    for (int i = 0; i < rows_; ++i)
    {
        for (int j = 0; j < cols_; ++j)
        {
            auto &pop = grid_[index(i, j)].getPopulation();

            bool infectious = false;
            for (auto &agent : pop)
                if (agent->getState() == State::Infectious)
                    infectious = true;

            for (auto &agent : pop)
            {
                if (infectious)
                    agent->setState(State::Infectious);

                // find neighboring cells
                std::vector<std::pair<int, int>> possibleMoves;
                for (int di = -1; di <= 1; ++di)
                {
                    for (int dj = -1; dj <= 1; ++dj)
                    {
                        if (di == 0 && dj == 0)
                            continue;
                        int ni = i + di;
                        int nj = j + dj;
                        if (ni >= 0 && ni < rows_ && nj >= 0 && nj < cols_)
                            possibleMoves.push_back({ni, nj});
                    }
                }

                if (!possibleMoves.empty())
                {
                    static std::random_device rd;
                    static std::mt19937 gen(rd());
                    std::uniform_int_distribution<> dis(0, possibleMoves.size() - 1);
                    int choice = dis(gen);

                    moves.push_back({agent, i, j, possibleMoves[choice].first, possibleMoves[choice].second});
                }
            }
        }
    }

    // PHASE 2: apply all moves
    for (auto &m : moves)
    {
        grid_[index(m.fromI, m.fromJ)].RemovePerson(m.agent);
        grid_[index(m.toI, m.toJ)].AddPerson(m.agent);
    }
}
