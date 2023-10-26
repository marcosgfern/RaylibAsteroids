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

	player.SetProjectilePool(&projectiles);
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

	asteroids.Clear();
	GenerateAsteroids();

	projectiles.Clear();
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

		//UpdateAsteroidsProjectilesCollisions();

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
			player.Shoot(TargetFPS * ShootCoolingTimeInSeconds);
		}
	}
}

void Game::GenerateAsteroids()
{
	asteroids.AddElements(
		GetRandomValue(MinAsteroids, MaxAsteroids),
		WindowWidth,
		WindowHeight);
}

void Game::UpdateAsteroids()
{
	std::list<std::reference_wrapper<Asteroid>> activeAsteroids = asteroids.GetActiveElements();
	for (std::list<std::reference_wrapper<Asteroid>>::iterator asteroidIt = activeAsteroids.begin(); asteroidIt != activeAsteroids.end(); asteroidIt++)
	{
		asteroidIt->get().Update();
	}
}

void Game::UpdateProjectiles()
{
	std::list<std::reference_wrapper<Projectile>> activeProjectiles = projectiles.GetActiveElements();
	for (std::list<std::reference_wrapper<Projectile>>::iterator projectileIt = activeProjectiles.begin(); projectileIt != activeProjectiles.end(); projectileIt++)
	{
		projectileIt->get().Update();
	}
}

void Game::UpdatePlayerAsteroidsCollisions()
{
	/*std::list<Asteroid>::iterator asteroidIt = asteroids.begin();
	while (asteroidIt != asteroids.end())
	{
		if (CheckCollisionCircles(player.GetPosition(), player.GetRadius(), asteroidIt->GetPosition(), asteroidIt->GetRadius()))
			asteroids.erase(asteroidIt++);
		else
			asteroidIt++;
	}*/
}

void Game::UpdateAsteroidsProjectilesCollisions()
{
	/*std::list<Projectile>::iterator projectileIt = projectiles.begin();
	bool destroyCurrentAsteroid;

	for (std::list<Asteroid>::iterator asteroidIt = asteroids.begin(); asteroidIt != asteroids.end(); asteroidIt++)
	{
		destroyCurrentAsteroid = false;
		for (std::list<Projectile>::iterator projectileIt = projectiles.begin(); projectileIt != projectiles.end(); projectileIt++)
		{
			if (CheckCollisionCircles(projectileIt->GetPosition(), projectileIt->GetRadius(), asteroidIt->GetPosition(), asteroidIt->GetRadius()))
			{
				projectileIt = projectiles.erase(projectileIt);
				projectileIt--;
				
				destroyCurrentAsteroid = asteroidIt->Hit();
			}
		}

		if (destroyCurrentAsteroid)
		{
			asteroidIt = asteroids.erase(asteroidIt);
			asteroidIt--;
		}
	}*/
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
	std::list<std::reference_wrapper<Asteroid>> activeAsteroids = asteroids.GetActiveElements();
	for (std::list<std::reference_wrapper<Asteroid>>::iterator asteroidIt = activeAsteroids.begin(); asteroidIt != activeAsteroids.end(); ++asteroidIt)
	{
		asteroidIt->get().Draw();
	}
}

void Game::DrawProjectiles()
{
	std::list<std::reference_wrapper<Projectile>> activeProjectiles = projectiles.GetActiveElements();
	for (std::list<std::reference_wrapper<Projectile>>::iterator projectileIt = activeProjectiles.begin(); projectileIt != activeProjectiles.end(); ++projectileIt)
	{
		projectileIt->get().Draw();
	}
}
