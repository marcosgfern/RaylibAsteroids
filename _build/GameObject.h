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
	bool active;

	Texture2D sprite;

public:
	GameObject();
	Vector2 GetPosition();
	void SetPosition(Vector2 newPosition);
	void SetRotation(float newRotation);
	float GetRadius();
	bool IsActive();
	void SetActive(bool value);

	void Update();
	void Move();
	
	void Draw();
};
