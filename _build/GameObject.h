#pragma once

#include "raylib.h"
#include "raymath.h"

class GameObject
{
protected:
	Vector2 position;
	Vector2 speed;
	int radius;
	float rotation;

	Texture2D sprite;

public:
	void Update();
	void Move();
	
	void Draw();
};
