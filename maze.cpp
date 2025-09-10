#include "maze.hpp"
#include <iostream>
#include <fstream>
#include <stack>
#include <set>
#include <unordered_map>
#include <algorithm>
using namespace std;

Maze::Maze(const string& filename) {
    ifstream in(filename);
    if (!in) {
        cerr << "Error: could not open file " << filename << endl;
        exit(1);
    }

    string line;
    while (getline(in, line)) {
        vector<int> row;
        for (char c : line) {
            if (c == '0' || c == '1') {
                row.push_back(c - '0');
            }
        }
        if (!row.empty()) grid.push_back(row);
    }

    rows = grid.size();
    cols = rows ? grid[0].size() : 0;

    // find start/target openings on border
    vector<pair<int,int>> openings;
    for (int c = 0; c < cols; c++) {
        if (grid[0][c] == 0) openings.push_back({0, c});
        if (grid[rows - 1][c] == 0) openings.push_back({rows - 1, c});
    }
    for (int r = 0; r < rows; r++) {
        if (grid[r][0] == 0) openings.push_back({r, 0});
        if (grid[r][cols - 1] == 0) openings.push_back({r, cols - 1});
    }

    if (openings.size() != 2) {
        cerr << "Maze must have exactly two openings on the border" << endl;
        exit(1);
    }

    start = openings[0];
    target = openings[1];
}

bool Maze::isValid(int r, int c) const {
    return r >= 0 && r < rows && c >= 0 && c < cols && grid[r][c] == 0;
}

bool Maze::solve() {
    stack<pair<int,int>> st;
    set<pair<int,int>> visited;
    unordered_map<int, pair<int,int>> parent; // map key = r*cols + c

    st.push(start);
    visited.insert(start);

    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    bool found = false;

    while (!st.empty()) {
        auto [r, c] = st.top();
        st.pop();

        if (make_pair(r, c) == target) {
            found = true;
            break;
        }

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i], nc = c + dc[i];
            if (isValid(nr, nc) && !visited.count({nr, nc})) {
                st.push({nr, nc});
                visited.insert({nr, nc});
                parent[nr * cols + nc] = {r, c};
            }
        }
    }

    if (!found) return false;

    // reconstruct path
    path.clear();
    pair<int,int> cur = target;
    while (cur != start) {
        path.push_back(cur);
        cur = parent[cur.first * cols + cur.second];
    }
    path.push_back(start);
    reverse(path.begin(), path.end());

    return true;
}

void Maze::printMaze(bool showPath) const {
    // Path lookup set for quick coloring
    set<pair<int,int>> pathSet(path.begin(), path.end());

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 1) {
                cout << "1";
            } else if (showPath && pathSet.count({r, c})) {
                cout << "\033[31m*\033[0m"; // red star
            } else {
                cout << "0";
            }
        }
        cout << "\n";
    }
}
