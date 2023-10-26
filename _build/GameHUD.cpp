#include "GameHUD.h"

void GameHUD::SetLifeSprite(Texture2D newLifeSprite)
{
	lifeSprite = newLifeSprite;
}

void GameHUD::Draw(int playerLifes, int points, int screenWidth, int screenHeight)
{
	DrawPlayerLifes(playerLifes, screenWidth, screenHeight);
	DrawPoints(points, screenWidth, screenHeight);
}

void GameHUD::DrawPlayerLifes(int playerLifes, int screenWidth, int screenHeight)
{
	for (int i = 0; i < playerLifes; i++)
	{
		DrawTexture(lifeSprite, 20 + 40 * i, screenHeight - 30, WHITE);
	}
}

void GameHUD::DrawPoints(int points, int screenWidth, int screenHeight)
{
	const char* pointsText = TextFormat("POINTS: %d", points);
	DrawText(
		pointsText, 
		screenWidth/2 - MeasureText(pointsText, 20)/2,
		20,
		20,
		WHITE);
}
