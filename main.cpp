#include <iostream>
#include "maze.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " inputfile\n";
        return 1;
    }

    try {
        Maze maze(argv[1]);
        if (maze.solve()) {
            std::cout << "Solution found:\n";
            maze.printMaze(true);
        } else {
            std::cout << "No solution possible.\n";
        }
    } catch (const std::exception &ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
