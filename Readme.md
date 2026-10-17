
# Monkey Typer — C++ & SFML

A real-time typing game developed in C++ using the SFML graphics library as part of a university programming project.

Players must type moving words before they reach the edge of the screen. The game includes adjustable difficulty, scoring, multiple fonts, and save/load functionality.

## Technologies Used

- C++17
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
| F7 | Switch to Roboto Bold font |
| F8 | Switch to Roboto Italic font |
| F9 | Switch to Roboto Regular font |
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
- `CMakeLists.txt` — CMake build configuration
- `words.txt` — Word database
- `Roboto-Regular.ttf` — Regular font
- `Roboto-Bold.ttf` — Bold font
- `Roboto-Italic.ttf` — Italic font
- `OFL.txt` — Roboto font license
- `Readme.md` — Project documentation


## Requirements

- C++17-compatible compiler
- CMake 3.25 or newer
- SFML 2.x
- Required font files:
  - `Roboto-Regular.ttf`
  - `Roboto-Bold.ttf`
  - `Roboto-Italic.ttf`
- Font license: SIL Open Font License (`OFL.txt`)

## Building the Project

The project uses CMake and SFML 2.6.

### macOS

The game has been successfully built and tested on an Apple Silicon Mac using CLion and SFML 2.6.2.

Install SFML using Homebrew:

```bash
brew install sfml@2
```

Open the project in CLion, reload CMake, and run the `MonkeyTyperSFML` target.

### Windows

Windows compatibility has not yet been tested.

Building on Windows requires a C++17-compatible compiler, CMake 3.25 or newer, and a compatible installation of SFML 2.6.

The SFML installation path may need to be configured manually.

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
