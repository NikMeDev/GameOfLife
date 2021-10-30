# Game Of Life
Yet another implementation of [John Conway's Game](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life "Wikipedia page")

## Downloading
```bash
git clone https://github.com/NikMeDev/GameOfLife.git
```
## Compiling
### Command-line version
```bash
g++ console.cpp GoL.cpp -o GoL
```
### GUI version
**To compile gui version you must install [sfml library](https://www.sfml-dev.org/ "SFML website").**
```bash
g++ gui.cpp GoL.cpp -o GoL -lsfml-graphics -lsfml-window -lsfml-system
```
## Usage
### Command-line version
```bash
./GoL <path to starting grid> [delay in ms (default=500)]
```
#### Example:
```bash
./GoL example.grid 1000
```
### GUI version
```bash
./GoL [wight] [height] //default is 70x70
```
#### Example:
```bash
./GoL 50 50
```
Controls are:
+ ***Enter*** - Start/Stop simulation
+ ***Arrow Up*** - Increase speed
+ ***Arrow Down*** - Decrease speed
+ ***Right click*** - Change cell state (live/dead)