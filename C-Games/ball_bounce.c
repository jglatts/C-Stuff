/*
	...Work in Progress...
*/
#include "raylib.h"
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 450
#define BAR_WIDTH	  90
#define BAR_HEIGHT	  10
#define PLAYER_RADIUS 20
#define MAX_BARS      50

typedef struct Bars
{
	Color color;
	int posX;
	int posY;
	bool active;
} Bars;

typedef struct BallPlayer 
{
	Vector2 position;
	Color color;
	int radius;
} BallPlayer;

Bars allBars[MAX_BARS] = {0};
BallPlayer player = {0};
bool gameStarted = false;

void InitBounceGame();
void UpdateBounceGame();
void DrawBounceGame();
void CheckSpaceKey();
void CheckLeftRight();
void CheckGameCollison();
void ResetScreen();

int main(void)
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "JDG : Ball Bounce");
	InitBounceGame();
	SetTargetFPS(60);
	// Main game loop
	while (!WindowShouldClose())
	{

		ResetScreen();
		UpdateBounceGame();
		DrawBounceGame();
		EndDrawing();
	}
	CloseWindow();
	return 0;
}

void InitBounceGame()
{
	srand((unsigned)time(NULL));
	player.radius = PLAYER_RADIUS;
	player.color = DARKBLUE;
	player.position = { (float)80 , (float)SCREEN_HEIGHT / 2 - player.radius };
	for (int i = 0; i < MAX_BARS; ++i) 
	{
		allBars[i].active = false;
		allBars[i].color = BLACK;
		// add detection so bars don't stack up
		allBars[i].posX = GetRandomValue(5, 600);
		allBars[i].posY = GetRandomValue(5, 400);
	}
}

void UpdateBounceGame() 
{
	if (gameStarted)
	{
		CheckGameCollison();
	}
	CheckSpaceKey();
	CheckLeftRight();
}

void CheckGameCollison()
{
	for (int i = 0; i < MAX_BARS; ++i)
	{
		Vector2 v = { player.position.x , player.position.y };
		Rectangle r = { allBars[i].posX, allBars[i].posY, BAR_WIDTH, BAR_HEIGHT };
		if (CheckCollisionCircleRec(v, PLAYER_RADIUS, r))
		{
			// add game logic here
			exit(1);
		}
	}
}

void CheckSpaceKey()
{
	if (IsKeyPressed(KEY_SPACE) || IsKeyDown(KEY_SPACE))
	{
		gameStarted = true;
		player.position.y -= 10;
	}
	else
	{
		player.position.y += .25;
	}
}

void CheckLeftRight()
{
	if (IsKeyPressed(KEY_LEFT) || IsKeyDown(KEY_LEFT))
	{
		gameStarted = true;
		player.position.x -= 5;
	}
	if (IsKeyPressed(KEY_RIGHT) || IsKeyDown(KEY_RIGHT))
	{
		gameStarted = true;
		player.position.x += 5;
	}
}

void DrawBounceGame()
{
	DrawCircle(player.position.x, player.position.y, PLAYER_RADIUS, BLUE);
	for (int i = 0; i < MAX_BARS; ++i)
	{
		DrawRectangle(allBars[i].posX, allBars[i].posY, BAR_WIDTH, BAR_HEIGHT, BLACK);		
	}
}

void ResetScreen() 
{
	BeginDrawing();
	ClearBackground(RAYWHITE);
}