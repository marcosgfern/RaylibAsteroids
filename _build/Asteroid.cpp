#include "Asteroid.h"
#include "Utilities.h"
#include "raylib.h"
#include "raymath.h"

#include <random>

static float BaseSpeed = 1;

static int RadiusBig = 40;
static int RadiusMedium = 30;
static int RadiusSmall = 20;

Texture2D Asteroid::BigSprite = {};
Texture2D Asteroid::MediumSprite = {};
Texture2D Asteroid::SmallSprite = {};

Asteroid::Asteroid(int windowWidth, int windowHeight)
{
	size = BIG;
	
	position = RandomSpawn(windowWidth, windowHeight);
	speed = Vector2Scale(Utilities::RandomNormalizedVector(), BaseSpeed);

	radius = RadiusBig;
}

void Asteroid::Update()
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

void Asteroid::Draw()
{
	switch (size)
	{
	case BIG:
	{
		Utilities::DrawTextureExCustom(BigSprite, position, 0.f, 1.f, WHITE);
	} break;
	case MEDIUM:
	{
		Utilities::DrawTextureExCustom(MediumSprite, position, 0.f, 1.f, WHITE);
	} break;
	case SMALL:
	{
		Utilities::DrawTextureExCustom(SmallSprite, position, 0.f, 1.f, WHITE);
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
