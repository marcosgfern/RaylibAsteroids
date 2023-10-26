#pragma once

#include "GameObject.h"

enum AsteroidSize
{
	BIG,
	MEDIUM,
	SMALL
};

class Asteroid : public GameObject
{
public:
	static Texture2D	BigSprite,
						MediumSprite,
						SmallSprite;

private:
	AsteroidSize size;

public:
	Asteroid(int screenWidth, int screenHeight);
	void SetSize(AsteroidSize newSize);

	void Reset(int screenWidth, int screenHeight);

	int Hit();

private:
	static Vector2 RandomSpawn(int screenWidth, int screenHeight);
};
