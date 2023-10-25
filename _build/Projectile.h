#include "raylib.h"

class Projectile
{
public:
	static Texture2D Sprite;

private:
	Vector2 position;
	Vector2 speed;
	int radius;

public:
	Projectile(Vector2 startingPosition, Vector2 normalizedSpeed);

	void Draw();
};
