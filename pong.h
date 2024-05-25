#ifndef PONG_H
#define PONG_H

#include <raylib.h>
#include <stdbool.h>

// Constants
#define STORAGE_DATA_FILE "storage.data"
#define SCREEN_HEIGHT 1360
#define SCREEN_WIDTH 720

// Enums
typedef enum GameScreen { Title = 0, Gameplay, Ending, EndScreen, Pause, vsCPU} GameScreen;
typedef enum StorageData { STORAGE_P1_SCORE = 0, STORAGE_P2_SCORE = 1 , STORAGE_CPU_SCORE = 2} StorageData;

// Global Variables
extern Rectangle boxA, boxB;
extern Vector2 ballPos, ballSpeed;
extern int radius, racketSpeed;
extern int winner, wincon, winnerScore, p1Score, p2Score,cpuScore, leftScore, rightScore;
extern bool pause;
extern bool exitWindowRequested;
extern bool exitWindow;
extern int gamemode;
extern float ballAcceleration;


// Function Prototypes
void InitializeElements(void);
GameScreen GameLogic(GameScreen currentState);
void DrawGame(GameScreen currentScreen);
void MoveBall(void);
void player_cpu(void);
bool Save(unsigned int position, int value);
int Load(unsigned int position);
bool file_exists(const char *filename);

#endif // PONG_H
