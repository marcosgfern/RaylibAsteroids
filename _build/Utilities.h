#pragma once

#include "raylib.h"
#include "raymath.h"

#include <random>

class Utilities
{
public:
	static void DrawTextureExCustom(Texture2D texture, Vector2 position, float rotation, float scale, Color tint);
	static Vector2 RandomNormalizedVector();
	static Vector2 RandomBorderSpawn();
	static Vector2 GetScreenCenter();
	static float DegreesToRadians(float degrees);
};
