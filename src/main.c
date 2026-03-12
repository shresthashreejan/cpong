#include "raylib.h"

#include "resource_dir.h"

int main ()
{
	// SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	const int screenWidth = 1280;
	const int screenHeight = 800;

	InitWindow(screenWidth, screenHeight, "Input keys");
	// SearchAndSetResourceDir("assets");

	Vector2 ballPosition = { (float)screenWidth/2, (float)screenHeight/2};

	while (!WindowShouldClose())
	{
		if (IsKeyDown(KEY_RIGHT)) ballPosition.x += 0.2f;
		if (IsKeyDown(KEY_LEFT)) ballPosition.x -= 0.2f;
		if (IsKeyDown(KEY_UP)) ballPosition.y -= 0.2f;
		if (IsKeyDown(KEY_DOWN)) ballPosition.y += 0.2f;
		BeginDrawing();
		ClearBackground(BLACK);
		DrawCircleV(ballPosition, 50, WHITE);
		DrawFPS(10, 10);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
