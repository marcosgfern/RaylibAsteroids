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
	Asteroid(Vector2 startingPosition);
};
