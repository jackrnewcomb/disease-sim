#include "Environment.hpp"

Environment::Environment(int xLen, int yLen)
{
    // Initialize row/column members
    rows_ = xLen;
    cols_ = yLen;

    // Set the size of cells_ and newCells_ to be the correct size of the grid
    grid_.resize(rows_ * cols_);
    newCells_.resize(rows_ * cols_);

    // For each cell...
    for (int i = 0; i < rows_; i++)
    {
        for (int j = 0; j < cols_; j++)
        {
            // Assign a random start
            Unit unit(i, j);
            unit.SetStartingPopulation();
            grid_[index(i, j)] = unit;
        }
    }
}

void Environment::updateSEQ()
{
    // For single threading, simply go through each cell and call updateCell()
    for (int i = 0; i < rows_; i++)
    {
        for (int j = 0; j < cols_; j++)
        {
            updateCell(i, j);
        }
    }
    // Swap content so cells_ now holds the most up to date data
    grid_.swap(newCells_);
}

inline void Environment::updateCell(int i, int j)
{
}
