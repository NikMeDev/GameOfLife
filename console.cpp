#include <fstream>
#include <iostream>
#include <chrono>
#include <thread>
#include <filesystem>
#include "GoL.hpp"

void clear()
{
    std::cout << "\x1B[2J\x1B[H";
}

void printGol(GoL gol)
{
    clear();
    for (size_t i = 0; i < gol.width; i++)
    {
        for (size_t j = 0; j < gol.height; j++)
        {
            std::cout <<  (gol(i, j) ? '@' : ' ');
        }
        std::cout << std::endl;
    }
}

GoL importGolFromFile(char path[])
{
    std::ifstream fin(path);
    size_t w, h;
    fin >> w >> h;
    GoL gol(w, h);
    for (size_t i = 0; i < w; i++)
    {
        for (size_t j = 0; j < h; j++)
        {
            bool alive = false;

            char input;
            fin >> input;
            if (input == '1')
                alive = true;

            gol(i, j) = alive;
        }
    }
    return gol;
}

int main(int argc, char *argv[])
{
    if (argc < 2 || !std::filesystem::exists(argv[1]))
    {
        std::cout << "Invalid arguments! Usage: " << argv[0] << "<path to grid> [delay in ms (default=500)]" << std::endl;
        return 2;
    }
    
    auto delay = std::chrono::milliseconds((argc > 2) ? std::stoi(std::string(argv[2])) : 500);

    GoL gol = importGolFromFile(argv[1]);
    
    while(true) {
        printGol(gol.grow());
        std::this_thread::sleep_for(delay);
    }
    return 0;
}