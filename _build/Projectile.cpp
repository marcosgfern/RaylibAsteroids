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

void Projectile::Update()
{
	position.x += speed.x;
	position.y += speed.y;

	float width = (float)GetScreenWidth();
	float height = (float)GetScreenHeight();

	if (position.x > width)
		position.x -= width;
	else if (position.x < 0)
		position.x += width;

	if (position.y > height)
		position.y -= height;
	else if (position.y < 0)
		position.y += height;
}

void Projectile::Draw()
{
	Utilities::DrawTextureExCustom(Sprite, position, 0.f, 1.f, WHITE);
}
