#include "raylib.h"

enum AsteroidSize
{
	BIG,
	MEDIUM,
	SMALL
};

class Asteroid
{
private:
	AsteroidSize size;

	Vector2 position;
	Vector2 speed;
	int radius;

public:
	Asteroid(int screenWidth, int screenHeight);



	void Draw();

private:
	Vector2 RandomSpawn(int screenWidth, int screenHeight);
};
