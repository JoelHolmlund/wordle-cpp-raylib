# Wordle C++ Clone

A desktop version of the popular game Wordle, developed as a personal project to learn C++ and graphics programming.

## Learning Journey
This was my first project using C++ and Raylib, created to learn the fundamentals of graphics programming and project structure. 

While I followed a tutorial to understand the core architecture, I have since expanded upon it by:
* Implementing custom JSON-loading for word lists.
* Refactoring the code into separate header and source files for better modularity.
* Adjusted game difficulty by tuning the maximum number of allowed guesses.
  
## Tech Stack
* **Language:** C++
* **Graphics:** [Raylib](https://www.raylib.com/)
* **Data:** JSON (handled via nlohmann/json)
* **Build Tool:** Make

## Key Features
* Custom word lists loaded via JSON.
* Optimized build process using a Makefile.
* Modular code structure with separated logic and UI.

## How to Run
1. Install [Raylib](https://github.com/raysan5/raylib).
2. Clone this repository.
3. Run `make` in the terminal to compile.
4. Execute with `./programmet`.
