#include "Game.h"
#include "raylib.h"

static int TargetFPS = 60;
static int WindowWidth = 800;
static int WindowHeight = 450;

static int MinAsteroids = 5;
static int MaxAsteroids = 15;

Game::Game()
{
	screen = LOGO;
	framesCounter = 0;
}

void Game::Initialize()
{
	InitWindow(WindowWidth, WindowHeight, "ASTEROIDS");

	SetTargetFPS(TargetFPS);

	RestartGameplay();
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

void Game::RestartGameplay()
{
	player.Reset();

	asteroids.clear();
	GenerateAsteroids();

	projectiles.clear();
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
	case GAMEPLAY:
	{
		if (IsKeyPressed(KEY_ENTER)) screen = ENDING;
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

	} break;
	case GAMEPLAY:
	{

	} break;
	case ENDING:
	{

	} break;
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

		DrawText(
			"PRESS [ENTER] to START",
			GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] to START", 20) / 2,
			GetScreenHeight() / 2 + 60, 20, GRAY);
	} break;
	case GAMEPLAY:
	{
		player.Draw();
		DrawAsteroids();
		DrawProjectiles();
		
	} break;
	case ENDING:
	{
		DrawText("ENDING SCREEN", 20, 20, 40, WHITE);
		DrawText("PRESS [ENTER] TO PLAY AGAIN",
			GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2,
			GetScreenHeight() / 2 + 80, 20, GRAY);
	} break;
	default: break;
	}

	EndDrawing();
}

void Game::GenerateAsteroids()
{
	int asteroidQuantity = GetRandomValue(MinAsteroids, MaxAsteroids);
	for (int i = 0; i < asteroidQuantity; i++)
	{
		asteroids.push_back(Asteroid(WindowWidth, WindowHeight));
	}
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

void Game::DrawAsteroids()
{
	std::list<Asteroid>::iterator asteroidIt;
	for (asteroidIt = asteroids.begin(); asteroidIt != asteroids.end(); ++asteroidIt)
	{
		asteroidIt->Draw();
	}
}

void Game::DrawProjectiles()
{
	std::list<Projectile>::iterator projectileIt;
	for (projectileIt = projectiles.begin(); projectileIt != projectiles.end(); ++projectileIt)
	{
		projectileIt->Draw();
	}
}
