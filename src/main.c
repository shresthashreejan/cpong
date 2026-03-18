#include <stdio.h>

#include "raylib.h"
#include "resource_dir.h"
#include "constants.h"

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

	Vector2 ballPosition = { (float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2 };
	Vector2 ballDirection = { -1.0f, -0.9f };

	Vector2 paddleOnePosition = { (float)SCREEN_WIDTH / 16, (float)SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2 };
	Vector2 paddleTwoPosition = { (float)SCREEN_WIDTH - (float)SCREEN_WIDTH / 16 - PADDLE_WIDTH, (float)SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2 };

	while (!WindowShouldClose())
	{
		float dt = GetFrameTime();
		float ballSpeed = BASE_SPEED * dt;
		float paddleSpeed = BASE_SPEED * dt;

		Rectangle paddleOne = { paddleOnePosition.x, paddleOnePosition.y, PADDLE_WIDTH, PADDLE_HEIGHT };

		Rectangle paddleTwo = { paddleTwoPosition.x, paddleTwoPosition.y, PADDLE_WIDTH, PADDLE_HEIGHT };

		Vector2 paddleOneDirection = {0};
		Vector2 paddleTwoDirection = {0};

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

		if (ballPosition.x <= SCREEN_PADDING + BALL_RADIUS || ballPosition.x >= SCREEN_WIDTH - SCREEN_PADDING - BALL_RADIUS)
		{
			ResetGame(&ballPosition, &ballDirection, &paddleOnePosition, &paddleTwoPosition);
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

		if (IsKeyPressed(KEY_R))
		{
			ResetGame(&ballPosition, &ballDirection, &paddleOnePosition, &paddleTwoPosition);
		}

		BeginDrawing();
		ClearBackground(BLACK);
		DrawCircleV(ballPosition, BALL_RADIUS, BLUE);
		DrawRectangleLines(SCREEN_PADDING, SCREEN_PADDING, SCREEN_WIDTH - SCREEN_PADDING * 2, SCREEN_HEIGHT - SCREEN_PADDING * 2, RAYWHITE);
		DrawRectangle(paddleOnePosition.x, paddleOnePosition.y, PADDLE_WIDTH, PADDLE_HEIGHT, RAYWHITE);
		DrawRectangle(paddleTwoPosition.x, paddleTwoPosition.y, PADDLE_WIDTH, PADDLE_HEIGHT, RAYWHITE);
		DrawFPS(10, 10);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}