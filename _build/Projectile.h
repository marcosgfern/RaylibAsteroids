#pragma once

#include "GameObject.h"

class Projectile : public GameObject
{
public:
	static Texture2D Sprite;

	Projectile(Vector2 startingPosition, Vector2 normalizedSpeed);
	Projectile(Vector2 startingPosition, float directionAngleInDegrees);

	void Reset(Vector2 startingPosition, float directionAngleInDegrees);
};