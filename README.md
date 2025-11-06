🟦 BSQ — Biggest Square Finder

This project implements a program that finds and marks the largest possible square on a rectangular map, avoiding obstacles.
It’s a classic algorithmic challenge widely used in coding schools (like 42) to practice memory allocation, file parsing, and dynamic programming.

📘 Description

The program reads a map from a text file, where each character represents a cell:
  9 -> numbers of lines
  . -> Empty cell (can be part of a square)
  o -> Obstacle
  x -> char to fill max squere
The first line defines map metadata in the following format:
  <number_of_lines> <empty_char> <obstacle_char> <full_char>


Example:
9 . o x
...........................
....o......................
............o..............
...........................
....o......................
...............o...........
...........................
......o..............o.....
..o.......o................

After processing, the program replaces the largest square of empty cells with the full_char (in this case, x).

⚙️ Compilation
A Makefile is provided.
Run: make

This will:
  . Create the build directory
  . Compile all sources
  . Automatically generate map.txt for testing
  . Produce the executable  "bsq"

▶️ Usage
Run the program with a map file:
  ./bsq map.txt
  cat map.txt | ./bsq
  ./bsq < map.txt

🧱 Project Structure
.
├── Makefile
├── main.c
├── bsq.c
├── bsq.h
├── map.txt        # generated automatically by Makefile
└── build/         # object files (created by make)

🧠 Algorithm Overview
The algorithm uses dynamic programming:
  1. Read and store the map into a 2D array.
  2. Create an auxiliary 2D array (dp) where each cell stores the size of the largest square ending at that position.
  3. Transition formula:
    dp[i][j] = min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + 1
  4. Track the cell with the maximum dp value → bottom-right corner of the largest square.
  5. Replace corresponding map cells with full_char.
This approach runs in O(n × m) time, where n and m are the map dimensions.

🧰 Cleaning and Rebuilding
make clean    # remove build directory and binary
make re       # rebuild everything

📄 License
This project is released for educational use under the MIT License.
