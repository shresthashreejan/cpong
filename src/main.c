#include <stdio.h>

#include "raylib.h"
#include "resource_dir.h"
#include "constants.h"

int main ()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib");
	// SearchAndSetResourceDir("assets");
	SetTargetFPS(120);

	Vector2 ballPosition = { (float)SCREEN_WIDTH/2, (float)SCREEN_HEIGHT/2};

	while (!WindowShouldClose())
	{
		float dt = GetFrameTime();
		float ballSpeed = BALL_BASE_SPEED * dt;

		Vector2 direction = {0};

		if (IsKeyDown(KEY_RIGHT)) direction.x += 1;
		if (IsKeyDown(KEY_LEFT)) direction.x -= 1;
		if (IsKeyDown(KEY_UP)) direction.y -= 1;
		if (IsKeyDown(KEY_DOWN)) direction.y += 1;

		ballPosition.x += direction.x * ballSpeed;
		ballPosition.y += direction.y * ballSpeed;

		BeginDrawing();
		ClearBackground(BLACK);
		DrawCircleV(ballPosition, 50, GRAY);
		DrawFPS(10, 10);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}