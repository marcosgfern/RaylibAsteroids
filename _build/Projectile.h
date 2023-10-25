#include "raylib.h"

class Projectile
{
private:
	Vector2 position;
	Vector2 speed;
	int radius;

public:
	Projectile(Vector2 startingPosition, Vector2 normalizedSpeed);

	void Draw();
};
