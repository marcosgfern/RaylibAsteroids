#pragma once

#include "Player.h"
#include "Asteroid.h"
#include "AsteroidPool.h"
#include "Projectile.h"
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

	Player player;
	AsteroidPool asteroids;
	std::list<Projectile> projectiles;

	int framesCounter;

public:
	Game();
	
	void Initialize();
	void RunLoop();

private:
	void LoadTextures();
	void RestartGameplay();

	void ProcessInput();
	void Update();
	void Draw();

	void ProcessMovementInput();

	void GenerateAsteroids();
	void AddProjectiles(std::list<Projectile> newProjectiles);

	void UpdateAsteroids();
	void UpdateProjectiles();

	void UpdatePlayerAsteroidsCollisions();
	void UpdateAsteroidsProjectilesCollisions();

	void ShowLogo(int timeInSeconds);
	void DrawAsteroids();
	void DrawProjectiles();
};