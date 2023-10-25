#include "Projectile.h"
#include "raylib.h"
#include "raymath.h"

static float BaseSpeed = 6;

Projectile::Projectile(Vector2 startingPosition, Vector2 normalizedSpeed)
{
	position = startingPosition;
	speed = Vector2Scale(normalizedSpeed, BaseSpeed);

	radius = 1;
}