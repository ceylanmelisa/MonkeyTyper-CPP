
# Monkey Typer — C++ & SFML

A real-time typing game developed in C++ using the SFML graphics library as part of a university programming project.

Players must type moving words before they reach the edge of the screen. The game includes adjustable difficulty, scoring, multiple fonts, and save/load functionality.

## Technologies Used

- C++20
- SFML 2.x
- CMake
- File I/O
- Object-Oriented Programming concepts

## Features

- Real-time word typing gameplay
- Words moving from right to left
- Dynamic difficulty adjustment
- Adjustable font size and word speed
- Save and load functionality
- High score tracking
- Multiple font support
- Background star effect
- Score history with timestamps
- Three-life system

## Controls

| Key | Action |
|-----|--------|
| Keyboard | Type the displayed words |
| F1 / F2 | Decrease / increase font size |
| F3 / F4 | Decrease / increase word speed |
| F5 | Save game |
| F6 | Load game |
| R | Restart after game over |
| ESC | Exit the game |

## Gameplay

- Words move from right to left across the screen.
- Each correctly typed word earns 10 points.
- The player starts with 3 lives.
- A life is lost when a word reaches the left edge.
- Difficulty increases every 15 seconds.
- The game ends when all lives are lost.

## Project Structure

- `main.cpp` — Main game implementation
- `CMakeLists.txt` — Build configuration
- `words.txt` — Word database
- `Readme.md` — Project documentation

## Requirements

- C++20-compatible compiler
- CMake 3.25 or newer
- SFML 2.x
- Required font files:
  - `arial.ttf`
  - `comic.ttf`
  - `times.ttf`

## Building the Project

The project uses CMake and SFML.

The current CMake configuration targets Windows with MinGW and downloads an SFML 2.5.1 Windows package.

The build configuration and font dependencies may require additional setup when cloning this repository.

## What I Learned

This university project helped me practice:

- Writing and organizing C++ code
- Handling keyboard input and game events
- Using a graphical library
- Implementing scoring and difficulty systems
- Reading and writing files
- Managing game state
- Working with CMake and external libraries

## Future Improvements

- Improve cross-platform compatibility
- Simplify SFML dependency management
- Improve the user interface
- Add additional game modes

## Author

Zarif Melisa Ceylan

Computer Science Student  
Polish-Japanese Academy of Information Technology (PJATK), Warsaw
