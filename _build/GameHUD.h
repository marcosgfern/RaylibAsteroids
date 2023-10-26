#pragma once
#include "raylib.h"
#include <string>

class GameHUD
{
private:
	Texture2D lifeSprite;
public:
	void SetLifeSprite(Texture2D newLifeSprite);

	void Draw(int playerLifes, int points, int screenWidth, int screenHeight);

private:
	void DrawPlayerLifes(int playerLifes, int screenWidth, int screenHeight);
	void DrawPoints(int points, int screenWidth, int screenHeight);
};