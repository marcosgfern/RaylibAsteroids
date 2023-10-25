#pragma once

#include "GameObject.h"
#include "raylib.h"

class Player : public GameObject
{
private:
	int lifes;

	int lastShotTimestamp;

public:
	Player();
	void SetSprite(Texture2D newSprite);

	void Reset();

	void SetSpeed(Vector2 rawDirection);
};
