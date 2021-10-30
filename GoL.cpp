#include <cstdlib>
#include <algorithm>
#include "GoL.hpp"

GoL::Grid::Grid(size_t width, size_t height)
{
    Grid::width = width;
    Grid::height = height;
    data = new bool[width * height];
}

bool GoL::Grid::operator()(size_t x, size_t y) const
{
    return data[y * width + x];
};

bool &GoL::Grid::operator()(size_t x, size_t y)
{
    return data[y * width + x];
};

GoL GoL::getGol()
{
    return *this;
}

GoL GoL::grow(int steps)
{
    for (int step = 0; step < steps; step++)
        progress();
    return getGol();
}

GoL::GoL(size_t width, size_t height)
{
    GoL::width = width;
    GoL::height = height;
    current = new Grid(width, height);
    next = new Grid(width, height);
};

void GoL::invert(size_t x, size_t y)
{
    (*current)(x, y) = !(*current)(x, y);
}

bool GoL::operator()(size_t x, size_t y) const
{
    return (*current)(x, y);
};

bool &GoL::operator()(size_t x, size_t y)
{
    return (*current)(x, y);
};

short GoL::countAliveNeigbors(size_t x, size_t y)
{
    short count = 0;
    for (size_t i = x - 1; i <= x + 1; i++)
    {
        for (size_t j = y - 1; j <= y + 1; j++)
        {
            if (i >= 0 && j >= 0 && i < width && j < height)
                count += (short)(*current)(i, j);
        }
    }
    if ((*current)(x, y))
        count--;
    return count;
}

void GoL::progress()
{
    for (size_t i = 0; i < width; i++)
    {
        for (size_t j = 0; j < height; j++)
        {
            short aliveNeigbors = countAliveNeigbors(i, j);
            if (aliveNeigbors == 2)
            {
                (*next)(i, j) = (*current)(i, j);
            }
            else if (aliveNeigbors == 3)
            {
                (*next)(i, j) = true;
            }
            else
            {
                (*next)(i, j) = false;
            }
        }
    }
    std::swap(current, next);
}