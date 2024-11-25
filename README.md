# C-PONG

A Pong game developed using the [Raylib](https://www.raylib.com/) library. Written in C.

## Key Features

* **Multiplayer:** Play against a friend in 2-player mode.
* **Singleplayer:** Challenge the AI in a Player vs CPU mode.
* **Game History:** Track your past games with a savefile system.

## Getting Started

### Prerequisites

* **Raylib:** Download and install the latest Raylib library from the official website: [https://www.raylib.com/](https://www.raylib.com/)
* **C Compiler:** C compiler like GCC or Clang is needed to compile the source code.

### Installation

1. Clone this repository:

   ```bash
   git clone https://github.com/DeCryptAF/C-PONG.git](https://github.com/ajwadmohtasim/C-PONG.git
   ```

2. Compile the source code:

   **Linux:**
   Refer to this [instruction](https://github.com/raysan5/raylib/wiki/Working-on-Windows).
   ```bash
   gcc -o pong main.c game.c savedata.c screen.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
   ```

   **Windows:**
   Refer to this [instruction](https://github.com/raysan5/raylib/wiki/Working-on-Windows).
   ```bash
   gcc -o pong main.c game.c savedata.c screen.c -lraylib -lopengl32 -lgdi32 -lwinmm
   ```

4. Run the game:

   ```bash
   ./pong  // Linux
   pong.exe  // Windows
   ```

## Known issues
- The collision of the ball and the paddle often glitches at certain angle. The observation is that the Collision system of the raylib considers all the four sides of the paddle when detecting a collision with the ball. Where We only need one side of each paddle,the front side, to keep the simplicity. 
