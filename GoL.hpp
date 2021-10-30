#include <cstdlib>
#include <algorithm>

class GoL
{
public:
    class Grid
    {
    public:
        Grid(size_t width, size_t height);
        bool operator()(size_t x, size_t y) const;
        bool &operator()(size_t x, size_t y);

    private:
        bool *data;
        size_t width;
        size_t height;
    };

    size_t width;
    size_t height;

    GoL getGol();
    GoL grow(int steps = 1);
    void invert(size_t x, size_t y);
    GoL(size_t width, size_t height);
    bool operator()(size_t x, size_t y) const;
    bool &operator()(size_t x, size_t y);

private:
    Grid *current;
    Grid *next;

    short countAliveNeigbors(size_t x, size_t y);
    void progress();
};