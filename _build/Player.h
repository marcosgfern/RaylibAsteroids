#include "raylib.h"

class Player
{
private:
	int lifes;

	int lastShotTimestamp;

	Vector2 position;
	Vector2 speed;
	int radius;
	float rotation;

public:
	Player(int totalLifes, Vector2 startingPosition);
};
