# Project 1 - Maze

## Student Information
Vishnu Pillai  
008724619  
https://github.com/vpillai002/CS315-Project1

## Collaboration and Sources
I used my own ideas and code, didn't feel the need to use AI to help debug as I used my own gdb when stuck. 
I did however, get stuck on some parts of syntax and for that, ChatGPT was very helpful, but I drew out  
logic on my own first to ensure integrity of the assignment.  

## Implementation Details
The maze is represented as a 2D grid of integers, where `1` represents a wall and `0` represents a path cell.  
The program first validates that the maze contains exactly two openings (`0`s) on the outer border. These are taken as the start and target cells.  

The solver uses an **iterative depth-first search (DFS)** implemented with an explicit stack data structure. At each step, the algorithm pops the current cell from the stack, checks if it is the target, and pushes all valid adjacent path cells (up, down, left, right) onto the stack if they have not yet been visited.  

If the target is reached, the path is reconstructed from the stored parent pointers and marked in the maze (e.g., with red `*`'s).  
If the stack becomes empty without reaching the target, the program reports `"No solution possible."`

Data structures used:
- 2D vector for storing the maze.
- Stack for managing DFS exploration.
- Parent map to reconstruct the path.
- Boolean visited state to avoid cycles.

## Testing & Status
It works as expected. I created two "maze" files, a "solve.txt" and a "unsolve.txt".  
The project compiles with `g++ -std=c++20 *.cpp`  
Running `./a.out solve.txt` will provide a maze with a path solved  
Running `./a.out unsolve.txt` will provide the `"No solution possible."`  