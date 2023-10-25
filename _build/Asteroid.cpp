#include "Asteroid.h"
#include "Utilities.h"
#include "raylib.h"
#include "raymath.h"

#include <random>

static float BaseSpeed = 3;

static int RadiusBig = 40;
static int RadiusMedium = 30;
static int RadiusSmall = 20;

Asteroid::Asteroid(int windowWidth, int windowHeight)
{
	size = BIG;
	
	position = RandomSpawn(windowWidth, windowHeight);
	speed = Vector2Scale(Utilities::RandomNormalizedVector(), BaseSpeed);

	radius = RadiusBig;
}

void Asteroid::Draw()
{
	switch (size)
	{
	case BIG:
	{
		DrawCircleV(position, RadiusBig, GREEN);
	} break;
	case MEDIUM:
	{
		DrawCircleV(position, RadiusMedium, YELLOW);
	} break;
	case SMALL:
	{
		DrawCircleV(position, RadiusSmall, RED);
	} break;
	default: break;
	}
}

Vector2 Asteroid::RandomSpawn(int windowWidth, int windowHeight)
{
	Vector2 spawn;

	//Vertical or horizontal border
	if (rand() % 2)
	{
		//Left or right
		if (rand() % 2) spawn.x = 0;
		else spawn.x = windowWidth - 1;

		spawn.y = GetRandomValue(0, windowHeight - 1);
	}
	else
	{
		//Top or bottom
		if (rand() % 2) spawn.y = 0;
		else spawn.y = windowHeight - 1;

		spawn.x = GetRandomValue(0, windowWidth - 1);
	}

	return spawn;
}
