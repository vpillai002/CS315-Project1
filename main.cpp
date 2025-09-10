#include "maze.hpp"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <maze-file>" << endl;
        return 1;
    }

    Maze m(argv[1]);

    if (m.solve()) {
        cout << "Solution found:\n";
        m.printMaze(true);
    } else {
        cout << "No solution possible.\n";
    }

    return 0;
}
