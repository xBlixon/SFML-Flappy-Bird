# Flappy bird clone (SFML)
This is a final project for Computer Programming course at the [Silesian University of Technology](https://www.polsl.pl/en/) for the fourth semester 2025/2026 of Informatics.

---
## About
This project is my first attempt at creating a 
game - simple Flappy bird clone done with SFML as foundation.

Idea is same as in the original game. Bird as playable character
whose goal is to jump through as many
obstacles made from 2 pipes separated by a gap.

## Project execution

SFML is used as a foundation of the project upon which
muliple interconnected components are made.

### Class description

- GameEngine – entrypoint for the game. Contains main game loop which delegates substasks (e.g. handling each GameObject on each frame, handling user inputs) to other classes.
- UserEventsHandler – gets event data from the GameEngine and contains logic related to non-gameplay interactions with the program.
- EntityManager – Stores all GameObjects and manages their state. Also responsible for in-game user interactions.
- ScoreManager – Simple class handling writing/reading highscore and game history to/from the hard disk with concurrency.
- GameResult – wrapper class of a single game playthrough record.
- State – Enum of possible game states:
	- MainMenu
	- Playing
	- Paused
	- GameOver
- GameObject – Abstract class of a base game object.
- Bird – extended by GameObject class of the playable character.
- Pipe – extended by GameObject class of simple obstacle.
- Menu - extended by GameObject class responsible for drawing Menu in any state other than Playing.
- Obstacle – composed of 2 Pipe objects making a complete obstacle of 2 pipes separated by a gap.

## Project requirements

- \<filesystem> - used for file handling for storing playthrough data and loading fonts. (ScoreManager, EntityManager)
- \<concept> - used as a gateway to the rendering logic by requiring objects meant to render to have a `draw()` method. (EntityManger)
- \<thread> - used for asynchronous fade in/out animation of obstacles and storing playthrough data. (Pipe and ScoreManager)
- \<ranges> - used to extract from playthrough history last 5 attempts. (Menu)

## Interaction

### Gameplay

The game allows for 2 inputs:
- Escape key - pausing the game.
- Spacebar - bird jump.

### Debug
F3 key - Toggle debug mode (indicated with opened imgui window)

In debug mode enabled:
- Middle mouse button (scrollwheel press) - drag camera to look beyond regular game view.
- CTRL + scrollwheel - zoom in/out game view.

## Graphical issue

> [!WARNING]
> In case where no text appear on the screen and unusual white squares are visible, it means that the font was not loaded.
> 
> In case of windows there should be no such issue since it first tries arial.ttf from the system font collection, on fail fallbacks
> to arial.ttf in the same directory of the `.exe`.
> 
> In case of unix-based systems the arial.ttf file must be in the same directory as the executable.

## Remarks
Due to limited time that I could spend on the project, in multiple spots a spaghetti code can be noticed. 
It is my first project of this kind and working on it gave me valuable
insight into my blind spots back in the design stage.

---
#### &copy; 2026 Xawier S³upik - Licensed under MIT License