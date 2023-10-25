#include "Projectile.h"
#include "Utilities.h"

static float BaseSpeed = 6;

Texture2D Projectile::Sprite = {};

Projectile::Projectile(Vector2 startingPosition, Vector2 normalizedSpeed)
{
	position = startingPosition;
	speed = Vector2Scale(normalizedSpeed, BaseSpeed);
	radius = 2;
	rotation = 0.f;

	sprite = Projectile::Sprite;
}
