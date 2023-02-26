# Mouse Trap

## Overview
Mouse Trap is a game developed in C language using the Allegro graphics library. The game is based on the classic game "Mouse Trap", which has similar mechanics to Pacman and was sold to the Atari platform. Mouse Trap is played by controlling a mouse through a maze, while avoiding cats and collecting cheese. The game consists of three levels, and the player must collect all the cheese in each level to progress to the next one. The player can use the arrow keys or the letters W, A, S and D to control the mouse. Each cheese collected generates 10 points, and each defeated cat generates 50 points. The game also features bones scattered throughout the maze that allow the mouse to transform into a dog for 5 seconds, allowing it to defeat the cats by touching them. 
Additionally, there are doors that can be opened or closed by pressing the letter B, making it easier for the mouse to escape. However, if a door is opened over the mouse or the cats, the mouse loses a life.

## Movement system demo
<iframe width="560" height="315" src="https://www.youtube.com/watch?v=13UFSrRgJsI&feature=youtu.be" frameborder="0" allowfullscreen></iframe>

## Features

- Three levels with distinct mazes and difficulties
- Randomly moving cats that will chase the mouse
- Bones that turn the mouse into a dog, allowing it to defeat the cats
- Doors that can be opened or closed to help the mouse escape
- Three lives for the mouse, and game over when all lives are lost
- Scoring system based on collected cheese and defeated cats

## Functions

Mouse Trap features several subroutines that were developed to improve the functionality of the code, prevent repetitions, and facilitate access to specific commands. Some of the functions include:
- permite_fechar(): Changes the state of the Fechar variable, allowing the main window to be closed when the command is executed.
- menu_principal(): Prints all the main elements used in the game's main menu on the screen. The main menu can be accessed by - opening the application or pressing the TAB key during the game (within a level).
- menu_principal_atualiza_retangulo(): A secondary function that draws a blue square in the positions where the cursor (the mouse's head) is not located, to avoid duplicating the sprite. Receives an integer variable as a parameter, indicating the position of the cursor.

## Screenshots
![MenuPreview](https://imgur.com/a/afNgdp6)

## Conclusion
The development of Mouse Trap allowed for the improvement of the knowledge acquired throughout the semester in the Algoritmos e Programação course, with a focus on the use of the C language and the Allegro graphics library. The game, while based on a classic, presents a cleaner and more detailed visual design, comparable to more modern games of the same genre. The project showcases the development of subroutines to optimize code functionality and offers a fun and challenging gaming experience.