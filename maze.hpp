#ifndef MAZE_HPP
#define MAZE_HPP

#include <string>
#include <vector>
#include <utility>

class Maze {
public:
    Maze(const std::string& filename);

    // Solve the maze iteratively using stack-based DFS
    bool solve();

    // Print maze, optionally showing the solution path
    void printMaze(bool showPath = false) const;

private:
    std::vector<std::vector<int>> grid;
    int rows, cols;
    std::pair<int, int> start, target;
    std::vector<std::pair<int, int>> path;

    bool isValid(int r, int c) const;
};

#endif // MAZE_HPP
