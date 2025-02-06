# A* Pathfinding Algorithm in C++

## Overview

This project implements the A* search algorithm in C++ to find the shortest path from a start position to a goal position on a grid-based board. The algorithm is designed to navigate around obstacles while minimizing the cost to reach the goal.

## Features

- Reads a board configuration from a file.
- Uses the A* algorithm to find the shortest path.
- Implements a heuristic function based on the Manhattan distance.
- Displays the resulting path in a user-friendly format.
- Includes unit tests for key functions.

## Usage

### Compilation

To compile the program, use a C++ compiler such as `g++`:

```sh
 g++ -std=c++17 main.cpp -o astar
```

### Running the Program

After compiling, execute the program:

```sh
 ./astar
```

Ensure that a valid board file (e.g., `1.board`) exists in the working directory.

## Board Representation

The board is represented as a text file with the following format:

- `0` represents an empty space.
- `1` represents an obstacle.

Example board file (`1.board`):

```
0,0,0,0,0,0
0,1,1,1,1,0
0,0,0,0,1,0
0,1,1,0,1,0
0,0,0,0,0,0
```

## Code Structure

- `main.cpp` - The main program that executes the A* search.
- `test.cpp` - Unit tests for verifying core functionalities.

## Testing

This project includes test functions to validate the correctness of the A* algorithm. The tests are executed within `main()` and verify functions such as:

- `Heuristic()`
- `AddToOpen()`
- `Compare()`
- `Search()`
- `CheckValidCell()`
- `ExpandNeighbors()`

## Example Output

The output of the program will be a visual representation of the path:

```
🚦   0   0   0   0   0   
0   ⛰️   ⛰️   ⛰️   ⛰️   0   
0   0   0   0   ⛰️   0   
0   ⛰️   ⛰️   0   ⛰️   0   
0   0   0   0   0   🏁   
```

Where:

- `🚦` represents the start position.
- `🏁` represents the goal position.
- `🚗` represents the path found.
- `⛰️` represents obstacles.

## License

This project is open-source and available under the MIT License.
