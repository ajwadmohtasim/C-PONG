#include <raylib.h>
#include <stdio.h>
#include <stdbool.h>
#include "pong.h"

// Global Variables Definition
Rectangle boxA, boxB;
Vector2 ballPos, ballSpeed;
int radius, racketSpeed = 10;
int winner, wincon = 5, winnerScore = 0, p1Score = 0, p2Score = 0, cpuScore = 0, leftScore = 0, rightScore = 0;
bool exitWindowRequested = false;
bool exitWindow = false;
int gamemode = 0;
float ballAcceleration = 1.0f;

// Main Function
//------------------------------------------------------------
int main()
{
    InitializeElements();
    ballSpeed.x = 300, ballSpeed.y = 500; //init ball speed
    GameScreen currentState = Title; // init screen
    SetExitKey(KEY_NULL); // Disable Exit

    while (!exitWindow)
    {
        currentState = GameLogic(currentState);
        BeginDrawing();
            DrawGame(currentState);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
