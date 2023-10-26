#include "Game.h"

static int TargetFPS = 60;
static int WindowWidth = 800;
static int WindowHeight = 450;

static int MinAsteroids = 8;
static int MaxAsteroids = 12;

static float ShootCoolingTimeInSeconds = 0.35f;

Game::Game()
{
	screen = LOGO;
	framesCounter = 0;
}

void Game::Initialize()
{
	InitWindow(WindowWidth, WindowHeight, "ASTEROIDS");
	SetTargetFPS(TargetFPS);

	LoadTextures();

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

void Game::LoadTextures()
{
	player.SetSprite(LoadTexture("resources/ship.png"));

	Projectile::Sprite = LoadTexture("resources/projectile.png");
	Asteroid::BigSprite = LoadTexture("resources/asteroid_big.png");
	Asteroid::MediumSprite = LoadTexture("resources/asteroid_medium.png");
	Asteroid::SmallSprite = LoadTexture("resources/asteroid_small.png");
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
		ProcessMovementInput();
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
		player.Update();
		UpdateAsteroids();
		UpdateProjectiles();
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

void Game::ProcessMovementInput()
{
	if (screen == GAMEPLAY)
	{
		Vector2 direction = { 0.f, 0.f };

		if (IsKeyDown(KEY_W)) direction.y -= 1.f;
		if (IsKeyDown(KEY_A)) direction.x -= 1.f;
		if (IsKeyDown(KEY_S)) direction.y += 1.f;
		if (IsKeyDown(KEY_D)) direction.x += 1.f;

		player.SetSpeed(direction);


		float rotationDirection = 0;

		if (IsKeyDown(KEY_LEFT)) rotationDirection -= 1.f;
		if (IsKeyDown(KEY_RIGHT)) rotationDirection += 1.f;

		player.SetRotation(rotationDirection);

		if (IsKeyDown(KEY_UP) && player.CanShoot())
		{
			AddProjectiles(player.Shoot(TargetFPS * ShootCoolingTimeInSeconds));
		}
	}
}

void Game::GenerateAsteroids()
{
	int asteroidQuantity = GetRandomValue(MinAsteroids, MaxAsteroids);
	for (int i = 0; i < asteroidQuantity; i++)
	{
		asteroids.push_back(Asteroid(WindowWidth, WindowHeight));
	}
}

void Game::AddProjectiles(std::list<Projectile> newProjectiles)
{
	std::list<Projectile>::iterator projectileIt;
	for (projectileIt = newProjectiles.begin(); projectileIt != newProjectiles.end(); ++projectileIt)
	{
		projectiles.push_back(*projectileIt);
	}
}

void Game::UpdateAsteroids()
{
	std::list<Asteroid>::iterator asteroidIt;
	for (asteroidIt = asteroids.begin(); asteroidIt != asteroids.end(); ++asteroidIt)
	{
		asteroidIt->Update();
	}
}

void Game::UpdateProjectiles()
{
	std::list<Projectile>::iterator projectileIt;
	for (projectileIt = projectiles.begin(); projectileIt != projectiles.end(); ++projectileIt)
	{
		projectileIt->Update();
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
