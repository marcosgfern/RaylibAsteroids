#include "Projectile.h"
#include "Utilities.h"
#include "raylib.h"
#include "raymath.h"

static float BaseSpeed = 6;

Texture2D Projectile::Sprite = {};

Projectile::Projectile(Vector2 startingPosition, Vector2 normalizedSpeed)
{
	position = startingPosition;
	speed = Vector2Scale(normalizedSpeed, BaseSpeed);

	radius = 2;
}

void Projectile::Draw()
{
	Utilities::DrawTextureExCustom(Sprite, position, 0.f, 1.f, WHITE);
}
