#include "Asteroid.h"
#include "Utilities.h"

#include <random>

static float BaseSpeed = 1.5f;

static int RadiusBig = 35;
static int RadiusMedium = 25;
static int RadiusSmall = 15;

Texture2D Asteroid::BigSprite = {};
Texture2D Asteroid::MediumSprite = {};
Texture2D Asteroid::SmallSprite = {};

Asteroid::Asteroid()
	:GameObject()
{
	position = Utilities::RandomBorderSpawn();
	speed = Vector2Scale(Utilities::RandomNormalizedVector(), BaseSpeed);

	SetSize(BIG);
}

void Asteroid::SetSize(AsteroidSize newSize)
{
	switch (newSize)
	{
	case BIG:
	{
		sprite = Asteroid::BigSprite;
		radius = RadiusBig;
	} break;
	case MEDIUM:
	{
		sprite = Asteroid::MediumSprite;
		radius = RadiusMedium;
	} break;
	case SMALL:
	{
		sprite = Asteroid::SmallSprite;
		radius = RadiusSmall;
	} break;
	default: break;
	}

	size = newSize;
}

void Asteroid::Reset(int screenWidth, int screenHeight)
{
	active = true;

	position = Utilities::RandomBorderSpawn();
	speed = Vector2Scale(Utilities::RandomNormalizedVector(), BaseSpeed);
	radius = RadiusBig;

	SetSize(BIG);
}

/// <returns>Points</returns>
int Asteroid::Hit()
{
	switch (size)
	{
	case BIG:
		SetSize(MEDIUM);
		return 10;
	case MEDIUM:
		SetSize(SMALL);
		return 20;
	case SMALL:
		active = false;
		return 30;
	default: break;
	}
}
