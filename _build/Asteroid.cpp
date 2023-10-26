#include "Asteroid.h"
#include "Utilities.h"

#include <random>

static float BaseSpeed = 1.5f;

static int RadiusBig = 40;
static int RadiusMedium = 30;
static int RadiusSmall = 20;

Texture2D Asteroid::BigSprite = {};
Texture2D Asteroid::MediumSprite = {};
Texture2D Asteroid::SmallSprite = {};

Asteroid::Asteroid(int screenWidth, int screenHeight)
	:GameObject()
{
	position = RandomSpawn(screenWidth, screenHeight);
	speed = Vector2Scale(Utilities::RandomNormalizedVector(), BaseSpeed);
	radius = RadiusBig;

	SetSize(BIG);
}

void Asteroid::SetSize(AsteroidSize newSize)
{
	switch (newSize)
	{
	case BIG: sprite = Asteroid::BigSprite;
		break;
	case MEDIUM: sprite = Asteroid::MediumSprite;
		break;
	case SMALL: sprite = Asteroid::SmallSprite;
		break;
	default: break;
	}

	size = newSize;
}

void Asteroid::Reset(int screenWidth, int screenHeight)
{
	active = true;

	position = RandomSpawn(screenWidth, screenHeight);
	speed = Vector2Scale(Utilities::RandomNormalizedVector(), BaseSpeed);
	radius = RadiusBig;

	SetSize(BIG);
}

void Asteroid::Hit()
{
	switch (size)
	{
	case BIG:
		SetSize(MEDIUM);
		break;
	case MEDIUM:
		SetSize(SMALL);
		break;
	case SMALL:
		active = false;
		break;
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
