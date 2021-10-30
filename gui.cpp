#include <SFML/Graphics.hpp>
#include <algorithm>
#include <fstream>
#include <filesystem>
#include <iostream>
#include "GoL.hpp"

int main(int argc, char *argv[])
{
    sf::Clock clock;
    bool started = false;
    size_t tableWidth;
    size_t tableHeight;
    if(argc == 3) {
        tableWidth = std::stoi(argv[1]);
        tableHeight = std::stoi(argv[2]);
    } else 
    {
        tableWidth = 70;
        tableHeight = 70;
    }

    GoL gol(tableWidth, tableHeight);

    unsigned int delay = 200;

    sf::RenderWindow window(sf::VideoMode(1500, 1500), "Game of Life");

    while (window.isOpen())
    {
        sf::Vector2u windowSize = window.getSize();
        float wight = windowSize.x;
        float height = windowSize.y;
        float cellSize = std::min(wight / gol.width, height / gol.height);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Enter)
                {
                    started = !started;
                }
                if (event.key.code == sf::Keyboard::Up)
                {
                    if(delay > 10) delay -= 10;
                }
                if (event.key.code == sf::Keyboard::Down)
                {
                    if(delay < 2000) delay += 10;
                }
            }
            if (event.type == sf::Event::MouseButtonPressed && !started)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    unsigned long long cellX = event.mouseButton.x / cellSize;
                    unsigned long long cellY = event.mouseButton.y / cellSize;
                    gol.invert(cellX, cellY);
                }
            }
            if (event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (started && clock.getElapsedTime().asMilliseconds() > delay)
        {
            clock.restart();
            gol.grow();
        }

        sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
        cell.setOutlineThickness(3.f);
        cell.setOutlineColor(sf::Color(0, 0, 0));
        window.clear(sf::Color(0, 0, 0));
        for (int i = 0; i < gol.width; i++)
        {
            for (int j = 0; j < gol.height; j++)
            {
                cell.setPosition(cellSize * i, cellSize * j);
                if (gol(i, j))
                {
                    cell.setFillColor(sf::Color(0, 0, 0));
                }
                else
                {
                    cell.setFillColor(sf::Color(255, 255, 255));
                }

                window.draw(cell);
            }
        }
        window.display();
    }

    return 0;
}