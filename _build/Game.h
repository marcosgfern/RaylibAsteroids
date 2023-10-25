#include "raylib.h"
#include "Player.h"
#include "Asteroid.h"
#include "Projectile.h"

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
	std::list<Asteroid> asteroids;
	std::list<Projectile> projectiles;

	int framesCounter;

public:
	Game();
	
	void Initialize();
	void RunLoop();

private:
	void NewGame();

	void ProcessInput();
	void Update();
	void Draw();

	void GenerateAsteroids();

	void ShowLogo(int timeInSeconds);

	void DrawAsteroids();
	void DrawProjectiles();
};