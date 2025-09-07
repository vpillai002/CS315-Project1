# Project 1 - Maze

## Student Information
Vishnu Pillai  
008724619  
https://github.com/vpillai002/CS315-Project1

## Collaboration and Sources
I used my own ideas and code, didn't feel the need to use AI to help debug as I used my own gdb when stuck. 

## Implementation Details

## Testing & Status
It works as expected. I created two "maze" files, a "solve.txt" and a "unsolve.txt". In order to test, I ran
g++ -std=c++20 *.cpp
./a.out solve.txt
./a.out unsolve.txt

The solve.txt is a maze that has a solution, and when run with ./a.out it outputs a solved maze. 
The unsolve.txt is a maze where no solution is possible simply outputs "No solution possible."