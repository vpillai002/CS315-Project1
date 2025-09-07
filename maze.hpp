#ifndef MAZE_HPP
#define MAZE_HPP

#include <vector>
#include <string>

struct Cell {
    int row;
    int col;
};

class Maze {
    private: 
        std::vector<std::vector<int>> grid;
        Cell start;
        Cell target;  
        int rows;
        int cols;
        void findStartAndTarget();

    public:
        Maze(const std::string& filename);
        bool solve();
        void printMaze(bool solved = false) const;

};

#endif // MAZE_HPP