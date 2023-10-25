#include "Asteroid.h"
#include "Utilities.h"
#include "raylib.h"
#include "raymath.h"

static float BaseSpeed = 3;

static float RadiusBig = 3;
static float RadiusMedium = 2;
static float RadiusSmall = 1;

Asteroid::Asteroid(Vector2 startingPosition)
{
	size = BIG;
	
	position = startingPosition;
	speed = Vector2Scale(Utilities::RandomNormalizedVector(), BaseSpeed);

	radius = RadiusBig;
}