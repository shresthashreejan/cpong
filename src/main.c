#include <stdio.h>

#include "raylib.h"
#include "resource_dir.h"
#include "constants.h"

typedef enum
{
	GAME_PLAYING,
	GAME_PAUSED,
	GAME_OVER
} GameState;

GameState gameState = GAME_PLAYING;

// Math
float ClampValue (float val, float min, float max)
{
	if (val < min) return min;
	if (val > max) return max;
	return val;
}

void ResetGame (Vector2 *ballPosition, Vector2 *ballDirection, Vector2 *paddleOnePosition, Vector2 *paddleTwoPosition)
{
	*ballPosition = (Vector2){ (float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2 };
	*ballDirection = (Vector2){ -1.0f, -0.9f };

	*paddleOnePosition = (Vector2){ (float)SCREEN_WIDTH / 16, (float)SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2 };
	*paddleTwoPosition = (Vector2){ (float)SCREEN_WIDTH - (float)SCREEN_WIDTH / 16 - PADDLE_WIDTH, (float)SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2 };
}

int main (void)
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib");
	SetTargetFPS(240);

	int playerOneScore = 0;
	int playerTwoScore = 0;

	int p1Width = MeasureText(PLAYER_ONE_WON, FONT_SIZE);
	int p2Width = MeasureText(PLAYER_TWO_WON, FONT_SIZE);

	Vector2 ballPosition = { (float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2 };
	Vector2 ballDirection = { -1.0f, -0.9f };

	Vector2 paddleOnePosition = { (float)SCREEN_WIDTH / 16, (float)SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2 };
	Vector2 paddleTwoPosition = { (float)SCREEN_WIDTH - (float)SCREEN_WIDTH / 16 - PADDLE_WIDTH, (float)SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2 };

	while (!WindowShouldClose())
	{

		if (IsKeyPressed(KEY_SPACE))
		{
			if (gameState == GAME_PLAYING) gameState = GAME_PAUSED;
			else if (gameState == GAME_PAUSED) gameState = GAME_PLAYING;
		}

		float dt = GetFrameTime();
		float ballSpeed = BASE_SPEED * dt;
		float paddleSpeed = BASE_SPEED * dt;

		Rectangle paddleOne = { paddleOnePosition.x, paddleOnePosition.y, PADDLE_WIDTH, PADDLE_HEIGHT };

		Rectangle paddleTwo = { paddleTwoPosition.x, paddleTwoPosition.y, PADDLE_WIDTH, PADDLE_HEIGHT };

		Vector2 paddleOneDirection = {0};
		Vector2 paddleTwoDirection = {0};

		if (gameState == GAME_PLAYING)
		{
			if (IsKeyDown(KEY_W)) paddleOneDirection.y -= 1;
			if (IsKeyDown(KEY_S)) paddleOneDirection.y += 1;
			if (IsKeyDown(KEY_UP)) paddleTwoDirection.y -= 1;
			if (IsKeyDown(KEY_DOWN)) paddleTwoDirection.y += 1;

			// Collision
			ballPosition.x += ballDirection.x * ballSpeed;
			ballPosition.y += ballDirection.y * ballSpeed;

			if (ballPosition.y <= SCREEN_PADDING + BALL_RADIUS || ballPosition.y >= SCREEN_HEIGHT - SCREEN_PADDING - BALL_RADIUS)
			{
				ballDirection.y *= -1;
			}

			if (ballPosition.x <= SCREEN_PADDING + BALL_RADIUS)
			{
				playerTwoScore++;
				if (playerTwoScore == WIN_SCORE)
				{
					gameState = GAME_OVER;
				}
				else
				{
					ResetGame(&ballPosition, &ballDirection, &paddleOnePosition, &paddleTwoPosition);
				}
			}

			if (ballPosition.x >= SCREEN_WIDTH - SCREEN_PADDING - BALL_RADIUS)
			{
				playerOneScore++;
				if (playerOneScore == WIN_SCORE)
				{
					gameState = GAME_OVER;
				}
				else
				{
					ResetGame(&ballPosition, &ballDirection, &paddleOnePosition, &paddleTwoPosition);
				}
			}

			if (CheckCollisionCircleRec(ballPosition, BALL_RADIUS, paddleOne))
			{
				ballDirection.x *= -1;
				ballPosition.x = paddleOne.x + PADDLE_WIDTH + BALL_RADIUS;
			}

			if (CheckCollisionCircleRec(ballPosition, BALL_RADIUS, paddleTwo))
			{
				ballDirection.x *= -1;
				ballPosition.x = paddleTwo.x - BALL_RADIUS;
			}

			paddleOnePosition.y += paddleOneDirection.y * paddleSpeed;
			paddleOnePosition.y = ClampValue(paddleOnePosition.y, SCREEN_PADDING, (float)SCREEN_HEIGHT - SCREEN_PADDING - PADDLE_HEIGHT);

			paddleTwoPosition.y += paddleTwoDirection.y * paddleSpeed;
			paddleTwoPosition.y = ClampValue(paddleTwoPosition.y, SCREEN_PADDING, (float)SCREEN_HEIGHT - SCREEN_PADDING - PADDLE_HEIGHT);

			if (gameState == GAME_OVER && IsKeyPressed(KEY_R))
			{
				playerOneScore = 0;
				playerTwoScore = 0;
				ResetGame(&ballPosition, &ballDirection, &paddleOnePosition, &paddleTwoPosition);
			}
		}

		BeginDrawing();
		ClearBackground(BLACK);
		DrawLine(SCREEN_WIDTH / 2, SCREEN_PADDING, SCREEN_WIDTH / 2, SCREEN_HEIGHT - SCREEN_PADDING, RAYWHITE);
		if (gameState == GAME_PAUSED)
		{
			DrawText("Paused", SCREEN_PADDING + 10, SCREEN_PADDING + 10, FONT_SIZE, RAYWHITE);
		}

		if (gameState == GAME_OVER)
		{
			if (playerOneScore == WIN_SCORE)
			{
				DrawText(PLAYER_ONE_WON, SCREEN_WIDTH / 4 - p1Width / 2, SCREEN_HEIGHT / 2, FONT_SIZE, RAYWHITE);
			}

			if (playerTwoScore == WIN_SCORE)
			{
				DrawText(PLAYER_TWO_WON, SCREEN_WIDTH * 3 / 4 - p2Width / 2, SCREEN_HEIGHT / 2, FONT_SIZE, RAYWHITE);
			}

			DrawText("Press R to Restart", SCREEN_PADDING + 10, SCREEN_HEIGHT - SCREEN_PADDING - FONT_SIZE, FONT_SIZE, RAYWHITE);
		}

		DrawCircleV(ballPosition, BALL_RADIUS, BLUE);
		DrawRectangleLines(SCREEN_PADDING, SCREEN_PADDING, SCREEN_WIDTH - SCREEN_PADDING * 2, SCREEN_HEIGHT - SCREEN_PADDING * 2, RAYWHITE);
		DrawRectangle(paddleOnePosition.x, paddleOnePosition.y, PADDLE_WIDTH, PADDLE_HEIGHT, RAYWHITE);
		DrawRectangle(paddleTwoPosition.x, paddleTwoPosition.y, PADDLE_WIDTH, PADDLE_HEIGHT, RAYWHITE);
		DrawText(TextFormat("%d", playerOneScore), SCREEN_WIDTH / 4, SCREEN_PADDING, 40, RAYWHITE);
		DrawText(TextFormat("%d", playerTwoScore), SCREEN_WIDTH * 3 / 4, SCREEN_PADDING, 40, RAYWHITE);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}