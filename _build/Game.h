#pragma once

#include "Player.h"
#include "Asteroid.h"
#include "AsteroidPool.h"
#include "Projectile.h"
#include "ProjectilePool.h"
#include "GameHUD.h"
#include "Utilities.h"

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
	int gameTimeCounter;

	int highScore;
	float highScoreTime;

	Player player;
	AsteroidPool asteroids;
	ProjectilePool projectiles;

	GameHUD hud;

	int framesCounter;

	Texture2D	logoTexture,
				titleTexture;

	Font customFont;

public:
	Game();
	
	void Initialize();
	void RunLoop();

private:
	void LoadResources();
	void RestartGameplay();
	void StartNewRound();
	void GameOver();

	void ProcessInput();
	void Update();
	void Draw();

	void ProcessMovementInput();

	void ShowLogo(int timeInSeconds);

	void GenerateAsteroids();

	void UpdateAsteroids();
	void UpdateProjectiles();

	void UpdatePlayerAsteroidsCollisions();
	void UpdateAsteroidsProjectilesCollisions();

	void DrawAsteroids();
	void DrawProjectiles();

	void DrawLogo();
	void DrawTitleScreen();
	void DrawEndingScreen();
};