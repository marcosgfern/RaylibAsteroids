#include "Game.h"

static int TargetFPS = 60;
static int WindowWidth = 800;
static int WindowHeight = 450;

static int MinAsteroids = 8;
static int MaxAsteroids = 12;

static float ShootCoolingTimeInSeconds = 0.35f;

static int NextScoreIncrement = 1000;

Game::Game()
{
	screen = LOGO;
	
	points = 0;
	gameTimeCounter = 0;
	highScore = 0;
	highScoreTime = 0.f;

	tripleShootNextScore = NextScoreIncrement;

	framesCounter = 0;

	player.SetProjectilePool(&projectiles);
}

void Game::Initialize()
{
	InitWindow(WindowWidth, WindowHeight, "ASTEROIDS");
	SetTargetFPS(TargetFPS);

	LoadResources();

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

void Game::LoadResources()
{
	logoTexture = LoadTexture("resources/logo.png");
	titleTexture = LoadTexture("resources/title.png");

	player.SetSprite(LoadTexture("resources/ship.png"));
	upgrade.SetSprite(LoadTexture("resources/triple_shot_upgrade.png"));
	hud.SetLifeSprite(LoadTexture("resources/ship.png"));

	Projectile::Sprite = LoadTexture("resources/projectile.png");
	Asteroid::BigSprite = LoadTexture("resources/asteroid_big.png");
	Asteroid::MediumSprite = LoadTexture("resources/asteroid_medium.png");
	Asteroid::SmallSprite = LoadTexture("resources/asteroid_small.png");

	customFont = LoadFont("resources/setback.png");
}

void Game::RestartGameplay()
{
	framesCounter = 0;

	points = 0;
	gameTimeCounter = 0;

	tripleShootNextScore = NextScoreIncrement;

	player.Reset();

	asteroids.Clear();
	GenerateAsteroids();

	projectiles.Clear();
}

void Game::StartNewRound()
{
	player.SetPosition({ (float)WindowWidth / 2, (float)WindowHeight / 2 });
	player.SetRotation(0.f);

	projectiles.Clear();
	GenerateAsteroids();
}

void Game::GameOver()
{
	screen = ENDING;
	framesCounter = 0;

	if (points > highScore)
	{
		highScore = points;
		highScoreTime = (float)gameTimeCounter / TargetFPS;
	}
}

void Game::ProcessInput()
{
	switch (screen)
	{
	case LOGO: break;
	case TITLE:
	{
		if (IsKeyPressed(KEY_ENTER))
		{
			screen = GAMEPLAY;
			RestartGameplay();
		}
	} break;
	case GAMEPLAY:
	{
		if (IsKeyPressed(KEY_ENTER))
		{
			GameOver();
		}
		ProcessMovementInput();
	} break;
	case ENDING:
	{
		if (IsKeyPressed(KEY_ENTER))
		{
			screen = TITLE;
			framesCounter = 0;
		}
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
		upgrade.Update();

		UpdatePlayerUpgradeCollision();
		UpdatePlayerAsteroidsCollisions();
		UpdateAsteroidsProjectilesCollisions();
		gameTimeCounter++;

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
		DrawLogo();
	}break;
	case TITLE:
	{
		DrawTitleScreen();
	} break;
	case GAMEPLAY:
	{
		upgrade.Draw();
		DrawProjectiles();
		DrawAsteroids();
		player.Draw();

		hud.Draw(player.GetLifes(), points, WindowWidth, WindowHeight);

	} break;
	case ENDING:
	{
		DrawEndingScreen();
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

void Game::ShowLogo(int timeInSeconds)
{
	framesCounter++;

	if (framesCounter > timeInSeconds * TargetFPS)
	{
		screen = TITLE;
		framesCounter = 0;
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
	if (activeAsteroids.empty())
	{
		StartNewRound();
	}
	else
	{
		for (std::list<std::reference_wrapper<Asteroid>>::iterator asteroidIt = activeAsteroids.begin(); asteroidIt != activeAsteroids.end(); asteroidIt++)
		{
			asteroidIt->get().Update();
		}
	}
}

void Game::UpdateProjectiles()
{
	std::list<std::reference_wrapper<Projectile>> activeProjectiles = projectiles.GetActiveElements();
	if (!activeProjectiles.empty())
	{
		for (std::list<std::reference_wrapper<Projectile>>::iterator projectileIt = activeProjectiles.begin(); projectileIt != activeProjectiles.end(); projectileIt++)
		{
			projectileIt->get().Update();
		}
	}
}

void Game::UpdatePlayerUpgradeCollision()
{
	if (upgrade.IsActive() && CheckCollisionCircles(
		player.GetPosition(), player.GetRadius(),
		upgrade.GetPosition(), upgrade.GetRadius()))
	{
		upgrade.SetActive(false);
		player.ActivateTripleShoot();
	}
}

void Game::UpdatePlayerAsteroidsCollisions()
{
	std::list<std::reference_wrapper<Asteroid>> activeAsteroids = asteroids.GetActiveElements();
	if (!activeAsteroids.empty())
	{
		for (std::list<std::reference_wrapper<Asteroid>>::iterator asteroidIt = activeAsteroids.begin(); asteroidIt != activeAsteroids.end(); asteroidIt++)
		{
			if (!player.IsInvincible() && CheckCollisionCircles(
				player.GetPosition(), player.GetRadius(),
				asteroidIt->get().GetPosition(), asteroidIt->get().GetRadius()))
			{
				if (player.Hit())
				{
					GameOver();
				}
			}
		}
	}
}

void Game::UpdateAsteroidsProjectilesCollisions()
{
	std::list<std::reference_wrapper<Asteroid>> activeAsteroids = asteroids.GetActiveElements();
	std::list<std::reference_wrapper<Projectile>> activeProjectiles = projectiles.GetActiveElements();

	if (!activeAsteroids.empty() && !activeProjectiles.empty())
	{
		for (std::list<std::reference_wrapper<Asteroid>>::iterator asteroidIt = activeAsteroids.begin(); asteroidIt != activeAsteroids.end(); asteroidIt++)
		{
			activeProjectiles = projectiles.GetActiveElements();
			for (std::list<std::reference_wrapper<Projectile>>::iterator projectileIt = activeProjectiles.begin(); projectileIt != activeProjectiles.end(); projectileIt++)
			{
				if (CheckCollisionCircles(
					projectileIt->get().GetPosition(), projectileIt->get().GetRadius(),
					asteroidIt->get().GetPosition(), asteroidIt->get().GetRadius()))
				{
					projectileIt->get().SetActive(false);
					AddPoints(asteroidIt->get().Hit());
					break;
				}
			}
		}
	}
}

void Game::AddPoints(int quantity)
{
	points += quantity;
	if (points >= tripleShootNextScore)
	{
		upgrade.Respawn();
		tripleShootNextScore += NextScoreIncrement;
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

void Game::DrawLogo()
{
	Utilities::DrawTextureExCustom(logoTexture, { (float)WindowWidth / 2, (float)WindowHeight / 2 }, 0.f, 1, WHITE);
}

void Game::DrawTitleScreen()
{
	framesCounter++;

	int titleHeight = -60 + framesCounter * 4;
	if (titleHeight >= 140) titleHeight = 140;
	Utilities::DrawTextureExCustom(titleTexture, { (float)WindowWidth / 2, (float)titleHeight }, 0.f, 1, WHITE);

	if ((framesCounter / 30) % 2 == 0) 
		DrawTextEx(
			customFont, 
			"PRESS [ENTER] to START", 
			{ (float)WindowWidth/2 - MeasureTextEx(customFont, "PRESS [ENTER] to START", 20, 5).x/2, (float)WindowHeight/2 + 60 },
			20,
			5,
			DARKGRAY);
}

void Game::DrawEndingScreen()
{
	framesCounter++;

	DrawTextEx(
		customFont, 
		"GAME OVER", 
		{ (float)WindowWidth / 2 - MeasureTextEx(customFont, "GAME OVER", 40, 10).x / 2, 30 },
		40, 
		10, 
		RED);

	const char* scoreText =
		TextFormat("SCORE: %d\n\nTIME: %.2f", points, (float)gameTimeCounter/TargetFPS);
	DrawText(
		scoreText,
		WindowWidth / 2 - MeasureText(scoreText, 20) / 2,
		100,
		20,
		WHITE);

	DrawTextEx(
		customFont,
		"HIGHSCORE",
		{ (float)WindowWidth / 2 - MeasureTextEx(customFont, "HIGHSCORE", 30, 7).x / 2, 200 },
		30,
		7,
		BLUE);

	const char* highScoreText = 
		TextFormat("SCORE: %d\n\nTIME: %.2f", highScore, highScoreTime);
	DrawText(
		highScoreText,
		WindowWidth / 2 - MeasureText(highScoreText, 20) / 2,
		250,
		20,
		SKYBLUE);

	if ((framesCounter / 30) % 2 == 0)
		DrawTextEx(
			customFont,
			"PRESS [ENTER] to PLAY AGAIN",
			{ (float)WindowWidth/2 - MeasureTextEx(customFont, "PRESS [ENTER] to PLAY AGAIN", 20, 5).x/2, (float)WindowHeight - 50 },
			20,
			5,
			DARKGRAY);
}
