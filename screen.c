#include "raylib.h"
#include "pong.h"

// Draw Each Frame
//------------------------------------------------------------
void DrawGame(GameScreen currentState)
{
    DrawFPS(2, 2);
    ClearBackground(WHITE);
    switch (currentState)
    {
        case Title:
            DrawText("PING PONG", GetScreenWidth() / 2, 20, 90, BLACK);
            DrawText(TextFormat("Player - 1 : %02d  ||  Player - 2 : %02d", p1Score, p2Score), GetScreenWidth() / 2, 150, 30, BLACK);
            DrawText(TextFormat("Player - 1 : %02d  ||  CPU : %02d", p1Score, cpuScore), GetScreenWidth() / 2, 190, 30, BLACK);
            DrawText("Player 1: W, S", 120, 360, 20, GRAY);
            DrawText("Player 2: I, K", 120, 390, 20, GRAY);
            DrawText("Press ENTER to PLAY \tvs Player - 2", 120, 420, 20, GRAY);
            DrawText("Press C \t\t\t\tto PLAY \tvs CPU", 120, 450, 20, GRAY);
            DrawText("Press SPACE to PAUSE", 120, 480, 20, GRAY);
            DrawText("Press ESCAPE to QUIT", 120, 510, 20, GRAY);
            break;
        case Gameplay:
            DrawCircleV(ballPos, (float)radius, BLACK); 
            DrawRectangleRec(boxA, BLACK);
            DrawRectangleRec(boxB, BLACK);
            DrawLine(SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK);
            DrawText(TextFormat("%02d", leftScore), GetScreenWidth() / 4, 50, 60, BLACK);
            DrawText(TextFormat("%02d", rightScore), (GetScreenWidth() / 4) * 3, 50, 60, BLACK);
            DrawText(TextFormat("Speed : %01lf", ballAcceleration), GetScreenWidth() / 4, 100, 20, BLACK);
            DrawText("Player - 1", (GetScreenWidth() / 8) * 3, 60, 30, BLACK);
            DrawText("Player - 2", (GetScreenWidth() / 8) * 4.5, 60, 30, BLACK);
            break;
        case Ending:
            ClearBackground(WHITE);
            DrawText(TextFormat("Winner is Player %d", winner), 120, 50, 60, BLACK);
            DrawText(TextFormat("Score: %d", winnerScore), 120, 120, 35, BLACK);
            DrawText("Press ENTER to PLAY AGAIN", 120, 420, 20, BLACK);
            DrawText("Press SPACE to goto TITLE", 120, 450, 20, BLACK);
            DrawText("Press ESCAPE to QUIT", 120, 480, 20, BLACK);
            break;
        case EndScreen:
            ClearBackground(WHITE);
            DrawText("Do you want to quit?   Y / N", 120, 420, 60, BLACK);
            break;
        case Pause:
            ClearBackground(WHITE);
            DrawText("PAUSED", 120, 420, 60, BLACK);
            DrawText("Space to continue", 120, 500, 20, BLACK);
            break;
        case vsCPU:
            DrawCircleV(ballPos, (float)radius, BLACK);
            DrawRectangleRec(boxA, BLACK);
            DrawRectangleRec(boxB, BLACK);
            DrawLine(SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK);
            DrawText(TextFormat("%02d", leftScore), GetScreenWidth() / 4, 50, 60, BLACK);
            DrawText(TextFormat("%02d", rightScore), (GetScreenWidth() / 4) * 3, 50, 60, BLACK);
            DrawText(TextFormat("Speed : %01lf", ballAcceleration), GetScreenWidth() / 4, 100, 20, BLACK);
            DrawText("Player - 1", (GetScreenWidth() / 8) * 3, 60, 30, BLACK);
            DrawText("CPU", (GetScreenWidth() / 8) * 4.5, 60, 30, BLACK);
            break;
        default:
            break;
    }
}