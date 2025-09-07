#include "maze.hpp"
#include <iostream>
#include <fstream>
#include <stack>
#include <stdexcept>

Maze::Maze(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        throw std::runtime_error("Could not open file");
    }

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::vector<int> row;
        for (char ch : line) {
            if (ch == '0' || ch == '1') row.push_back(ch - '0'); 
        }
        if (!row.empty()) grid.push_back(row);
    }
    rows = grid.size();
    cols = rows ? grid[0].size() : 0;

    if (rows == 0 || cols == 0) {
        throw std::runtime_error("Empty or invalid maze");
    }

    findStartAndTarget();
}

void Maze::findStartAndTarget() {
    bool foundStart = false;
    bool foundTarget = false;
    
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 0 && (r == 0 || r == rows - 1 || c == 0 || c == cols - 1)) {
                if (!foundStart) {
                    start = {r, c};
                    foundStart = true;
                } else if (!foundTarget) {
                    target = {r, c};
                    foundTarget = true;
                }
            }
        }
    }

    if (!foundStart || !foundTarget) {
        throw std::runtime_error("Maze must have exactly two openings on the border");
    }
}

bool Maze::solve() {
    std::stack<Cell> s;
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));

    s.push(start);
    visited[start.row][start.col] = true;

    while (!s.empty()) {
        Cell current = s.top();

        if (current.row == target.row && current.col == target.col) {
            // Found a solution -> mark the path
            while (!s.empty()) {
                Cell pathCell = s.top();
                s.pop();
                grid[pathCell.row][pathCell.col] = -1; // Mark path
            }
            return true; // Solved
        }

        bool moved = false;
        const int dr[4] = {-1, 1, 0, 0};
        const int dc[4] = {0, 0, -1, 1};
        for (int i = 0; i < 4; i++) {
            int newRow = current.row + dr[i];
            int newCol = current.col + dc[i];
            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols &&
                grid[newRow][newCol] == 0 && !visited[newRow][newCol]) {
                s.push({newRow, newCol});
                visited[newRow][newCol] = true;
                moved = true;
                break; // take first valid move
            }
        }

        if (!moved) {
            s.pop(); // backtrack
        }
    }
    return false; // No solution
}

void Maze::printMaze(bool solved) const {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 1) {
                std::cout << "1";
            } else if (grid[r][c] == -1) {
                // path cell
                if (solved) {
                    std::cout << "\033[32m*\033[0m";  // or: 
                } else {
                    std::cout << "0";
                }
            } else {
                std::cout << "0";
            }
        }
        std::cout << "\n";
    }
}