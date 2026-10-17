# MonkeyTyperSFML

MonkeyTyperSFML is a fast-paced typing game where words move across the screen, and players need to type them correctly before they disappear. The game features dynamic difficulty, customizable settings, and a high score system.

## Features

- Real-time word typing gameplay
- Dynamic difficulty adjustment
- Customizable font size and game speed
- Save/Load game functionality
- High score tracking
- Multiple font support
- Background star effect
- Score history with timestamps

## Requirements

- SFML 2.x
- C++20 compatible compiler
- Font files:
    - arial.ttf
    - comic.ttf
- words.txt file containing word list

## Controls

- **Type** the words as they appear on screen
- **F1/F2**: Decrease/Increase font size
- **F3/F4**: Decrease/Increase word speed
- **F5**: Save game
- **F6**: Load game
- **R**: Restart game after game over
- **ESC**: Exit game

## Gameplay

- Words move from right to left across the screen
- Type words exactly as they appear to score points
- Each correct word gives you 10 points
- You have 3 lives - lose one each time a word reaches the left side
- Game difficulty increases every 15 seconds
- The game ends when you lose all lives

## Building the Project

The project uses CMake as its build system. To build:
