#pragma once

#include "Player.h"
#include "Asteroid.h"
#include "AsteroidPool.h"
#include "Projectile.h"
#include "ProjectilePool.h"
#include "GameHUD.h"

#include "raylib.h"

#include <list>

enum GameScreen
{
	LOGO,
	TITLE,
	GAMEPLAY,
	ENDING
};

class Game
{
private:
	GameScreen screen;

	int points;

	Player player;
	AsteroidPool asteroids;
	ProjectilePool projectiles;

	GameHUD hud;

	int framesCounter;

public:
	Game();
	
	void Initialize();
	void RunLoop();

private:
	void LoadTextures();
	void RestartGameplay();
	void StartNewRound();

	void ProcessInput();
	void Update();
	void Draw();

	void ProcessMovementInput();

	void GenerateAsteroids();

	void UpdateAsteroids();
	void UpdateProjectiles();

	void UpdatePlayerAsteroidsCollisions();
	void UpdateAsteroidsProjectilesCollisions();

	void ShowLogo(int timeInSeconds);
	void DrawAsteroids();
	void DrawProjectiles();
};