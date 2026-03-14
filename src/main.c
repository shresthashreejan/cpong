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

int main (void)
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib");
	SetTargetFPS(240);

	const float BALL_RADIUS = 12.0f;
	const float PADDLE_WIDTH = 20.0f;
	const float PADDLE_HEIGHT = 80.0f;

	Vector2 ballPosition = { (float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2 };
	Vector2 paddleOnePosition = { (float)SCREEN_WIDTH / 16, (float)SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2 };
	Vector2 paddleTwoPosition = { (float)SCREEN_WIDTH - (float)SCREEN_WIDTH / 16 - PADDLE_WIDTH, (float)SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2 };

	while (!WindowShouldClose())
	{
		float dt = GetFrameTime();
		float ballSpeed = BASE_SPEED * dt;
		float paddleSpeed = BASE_SPEED * dt;

		Vector2 ballDirection = {0};
		Vector2 paddleOneDirection = {0};
		Vector2 paddleTwoDirection = {0};

		if (IsKeyDown(KEY_W)) paddleOneDirection.y -= 1;
		if (IsKeyDown(KEY_S)) paddleOneDirection.y += 1;
		if (IsKeyDown(KEY_UP)) paddleTwoDirection.y -= 1;
		if (IsKeyDown(KEY_DOWN)) paddleTwoDirection.y += 1;

		paddleOnePosition.y += paddleOneDirection.y * paddleSpeed;
		paddleOnePosition.y = ClampValue(paddleOnePosition.y, 0.0f, (float)SCREEN_HEIGHT - PADDLE_HEIGHT);

		paddleTwoPosition.y += paddleTwoDirection.y * paddleSpeed;
		paddleTwoPosition.y = ClampValue(paddleTwoPosition.y, 0.0f, (float)SCREEN_HEIGHT - PADDLE_HEIGHT);

		BeginDrawing();
		ClearBackground(BLACK);
		DrawCircleV(ballPosition, BALL_RADIUS, BLUE);
		DrawRectangle(paddleOnePosition.x, paddleOnePosition.y, PADDLE_WIDTH, PADDLE_HEIGHT, RAYWHITE);
		DrawRectangle(paddleTwoPosition.x, paddleTwoPosition.y, PADDLE_WIDTH, PADDLE_HEIGHT, RAYWHITE);
		DrawFPS(10, 10);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}