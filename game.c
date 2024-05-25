#include <raylib.h>
#include "pong.h"
#include <stdio.h>

// Game Lgoic
//------------------------------------------------------------
GameScreen GameLogic(GameScreen currentState)
{
    // Screen + Game Logics
    switch (currentState)
    {
        // Title Screen
        case Title:
            if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                currentState = Gameplay, gamemode = Gameplay;
            if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE))
                exitWindow = true;
            if (IsKeyDown(KEY_C))
                currentState = vsCPU, gamemode = vsCPU;
            break;
        
        // Player Vs Player
        case Gameplay:
            // Ball Movement Function
            MoveBall();

            // Left Racket
            if (IsKeyDown(KEY_W) && boxA.y > 0)
                boxA.y -= racketSpeed;
            if (IsKeyDown(KEY_S) && boxA.y < GetScreenHeight() - boxA.height)
                boxA.y += racketSpeed;
            
            // Right Racket
            if (IsKeyDown(KEY_I) && boxB.y > 0)
                boxB.y -= racketSpeed;
            if (IsKeyDown(KEY_K) && boxB.y < GetScreenHeight() - boxB.height)
                boxB.y += racketSpeed;

            // Check if won
            if (((leftScore >= wincon) || (rightScore >= wincon)) && gamemode == Gameplay)
            {
                winner = (leftScore > rightScore) ? 1 : 2;
                
                // Save score in savedata.data
                if (winner == 1)
                {
                    Save(STORAGE_P1_SCORE, ++p1Score);
                    Save(STORAGE_P2_SCORE, p2Score);
                }
                else
                {
                    Save(STORAGE_P1_SCORE, p1Score);
                    Save(STORAGE_P2_SCORE, ++p2Score);
                }

                // Update Scores
                winnerScore = (leftScore > rightScore) ? leftScore : rightScore;
                rightScore = leftScore = 0;
                currentState = Ending;
            }

            // Pause menu
            if (IsKeyPressed(KEY_SPACE))
                currentState = Pause;

            //  Check if "want to quit"
            if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE))
                exitWindowRequested = true;
            if (exitWindowRequested)
                currentState = EndScreen;
            break;

        // Ending Screen after Game is over
        case Ending:
            if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                currentState = (gamemode == Gameplay) ? Gameplay : vsCPU;
            if (IsKeyPressed(KEY_SPACE))
                currentState = Title;
            if (IsKeyPressed(KEY_ESCAPE))
                exitWindow = true;
            break;

        // Requesting Quit Screen
        case EndScreen:
            if (exitWindowRequested)
            {
                // Y = Yes , exit game
                if (IsKeyPressed(KEY_Y))
                    exitWindow = true;
                // N / Escape - No, don't exit game
                else if (IsKeyPressed(KEY_N) || IsKeyPressed(KEY_ESCAPE))
                    exitWindowRequested = false;
            }
            else
                currentState = (gamemode == Gameplay) ? Gameplay : vsCPU;
            break;

        // Pause Screen
        case Pause:
            if (IsKeyPressed(KEY_SPACE))
                currentState = (gamemode == Gameplay) ? Gameplay : vsCPU;
            break;

        // Player vs player_cpu
        case vsCPU:
            MoveBall();

            player_cpu();

            if (IsKeyDown(KEY_W) && boxA.y > 0)
                boxA.y -= racketSpeed;
            if (IsKeyDown(KEY_S) && boxA.y < GetScreenHeight() - boxA.height)
                boxA.y += racketSpeed;

            // Check if won
            if (((leftScore >= wincon) || (rightScore >= wincon)) && gamemode == vsCPU)
            {
                winner = (leftScore > rightScore) ? 1 : 2;
                
                // Save score in savedata.data
                if (winner == 1)
                {
                    Save(STORAGE_P1_SCORE, ++p1Score);
                    Save(STORAGE_CPU_SCORE, p2Score);
                }
                else
                {
                    Save(STORAGE_P1_SCORE, p1Score);
                    Save(STORAGE_CPU_SCORE, ++p2Score);
                }
                
                // Update Scores
                winnerScore = (leftScore > rightScore) ? leftScore : rightScore;
                rightScore = leftScore = 0;
                
                // Update screen
                currentState = Ending;
            }

            // Pause menu
            if (IsKeyPressed(KEY_SPACE))
                currentState = Pause;

            //  Check if "want to quit"
            if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE))
                exitWindowRequested = true;
            if (exitWindowRequested)
                currentState = EndScreen;

            break;

        // Default Case
        default:
            break;
    }

    //Returning current state so we can use DrawGame()
    return currentState;
}

// Intialize The Game 
//------------------------------------------------------------
void InitializeElements(void)
{
    InitWindow(SCREEN_HEIGHT, SCREEN_WIDTH, "PONG"); // Intialize Game Screen
    SetWindowState(FLAG_VSYNC_HINT); // Set Vsync for smooth gameplay

    // Ball properties
    ballPos = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    ballSpeed = (Vector2){5.0f, 4.0f};
    radius = 6;

    // Racket Properties
    boxA = (Rectangle){50, GetScreenHeight() / 2.0f - 50, 10, 100};
    boxB = (Rectangle){GetScreenWidth() - 50 - 10, GetScreenHeight() / 2 - 50, 10, 100};

    // Check if savefile exists, if not, go with default, else load save values.
    if (file_exists(STORAGE_DATA_FILE))
    {
        p1Score = Load(STORAGE_P1_SCORE);
        p2Score = Load(STORAGE_P2_SCORE);
        cpuScore = Load(STORAGE_CPU_SCORE);
    }
}

// Ball Movement Logic
//------------------------------------------------------------
void MoveBall(void)
{
    // Check Collision of the Ball with the Racket
    if (CheckCollisionCircleRec(ballPos, 6, boxA))
        ballSpeed.x *= -1, ballAcceleration+=.05;
    if (CheckCollisionCircleRec(ballPos, 6, boxB))
        ballSpeed.x *= -1, ballAcceleration+=.05;

     // Check Collision of the Ball with the Wall
    if (ballPos.y < 0)
        ballPos.y = 0, ballSpeed.y *= -1, ballAcceleration+=.05;
    if (ballPos.y > GetScreenHeight())
        ballPos.y = GetScreenHeight(), ballSpeed.y *= -1, ballAcceleration+=.05;

     // Check if it's a GOAL
    if (ballPos.x < 0 || ballPos.x > GetScreenWidth())
    {
        if (ballPos.x < 0)
            rightScore++;
        else if (ballPos.x > GetScreenWidth())
            leftScore++;
        ballPos = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
        ballAcceleration = 1.0f;
    }

    // Ball Position Update
    ballPos.x += ballSpeed.x * GetFrameTime() * ballAcceleration;
    ballPos.y += ballSpeed.y * GetFrameTime() * ballAcceleration;
}

// Player - player_cpu Logic
//------------------------------------------------------------
void player_cpu(void)
{   
    int yCenter = GetScreenHeight()/2.0f - 50; // y axis center

    // check if ball moves away from the player_cpu, reset position if it's yes
    if (ballPos.x < GetScreenWidth()*((ballAcceleration < 1.7) ? .80 : .7))
    {
        if (boxB.y > yCenter && boxB.y != yCenter) boxB.y -= (racketSpeed - 1);
        else if (boxB.y < yCenter && boxB.y != yCenter) boxB.y += (racketSpeed -1);
    }
    else
    {
        if (ballPos.y > (boxB.y + boxB.height/2))
            boxB.y += (racketSpeed - 1);
        if (ballPos.y < (boxB.y + boxB.height/2))
            boxB.y -= (racketSpeed - 1);
    }    
    
}
