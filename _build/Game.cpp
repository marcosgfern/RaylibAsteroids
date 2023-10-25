#include "Game.h"
#include "raylib.h"

static int TargetFPS = 60;

Game::Game()
{
	screen = LOGO;
	framesCounter = 0;
}

void Game::Initialize()
{
	InitWindow(800, 450, "ASTEROIDS");

	SetTargetFPS(TargetFPS);
}

void Game::RunLoop()
{
	while (!WindowShouldClose())
	{
		ProcessInput();
		Update();
		Draw();
	}
}

void Game::ProcessInput()
{
	switch (screen)
	{
	case LOGO: break;
	case TITLE:
	{
		if (IsKeyPressed(KEY_ENTER)) screen = GAMEPLAY;
	} break;
	case ENDING:
	{
		if (IsKeyPressed(KEY_ENTER)) screen = TITLE;
	} break;
	default: break;
	}
}

void Game::Update()
{
	switch (screen)
	{
	case LOGO:
	{
		ShowLogo(3);

	} break;
	case TITLE:
	{
		
	}
	case GAMEPLAY:
	{

	} break;
	case ENDING:
	{

	}

	default: break;
	}
}

void Game::Draw()
{
	BeginDrawing();
	ClearBackground(BLACK);

	switch (screen)
	{
	case LOGO:
	{
		DrawText("LOGO SCREEN", 20, 20, 40, WHITE);
	}break;
	case TITLE:
	{
		DrawText("TITLE SCREEN", 20, 20, 40, WHITE);
	} break;
	case GAMEPLAY:
	{
		DrawText("GAMEPLAY SCREEN", 20, 20, 40, WHITE);
	} break;
	case ENDING:
	{
		DrawText("ENDING SCREEN", 20, 20, 40, WHITE);
	} break;
	default: break;
	}

	EndDrawing();
}

void Game::ShowLogo(int timeInSeconds)
{
	framesCounter++;

	if (framesCounter > timeInSeconds * TargetFPS)
	{
		screen = TITLE;
		framesCounter = 0;
	}
}