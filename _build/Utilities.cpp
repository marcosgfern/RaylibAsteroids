#include "Utilities.h"

void Utilities::DrawTextureExCustom(Texture2D texture, Vector2 position, float rotation, float scale, Color tint)
{
    Rectangle source = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
    Rectangle dest = { position.x, position.y, (float)texture.width * scale, (float)texture.height * scale };
    Vector2 origin = { (float)texture.width / 2.f, (float)texture.height / 2.f };
    DrawTexturePro(texture, source, dest, origin, rotation, tint);
}

Vector2 Utilities::RandomNormalizedVector()
{
    Vector2 vector;

    vector.x = rand() / static_cast<float>(RAND_MAX);
    if ((rand() % 2)) vector.x *= -1;
    vector.y = rand() / static_cast<float>(RAND_MAX);
    if ((rand() % 2)) vector.y *= -1;

    return Vector2Normalize(vector);
}

Vector2 Utilities::RandomBorderSpawn()
{
	Vector2 spawn;

	//Vertical or horizontal border
	if (rand() % 2)
	{
		//Left or right
		if (rand() % 2) spawn.x = 0;
		else spawn.x = GetScreenWidth() - 1;

		spawn.y = GetRandomValue(0, GetScreenHeight() - 1);
	}
	else
	{
		//Top or bottom
		if (rand() % 2) spawn.y = 0;
		else spawn.y = GetScreenHeight() - 1;

		spawn.x = GetRandomValue(0, GetScreenWidth() - 1);
	}

	return spawn;
}

Vector2 Utilities::GetScreenCenter()
{
    return { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
}

float Utilities::DegreesToRadians(float degrees)
{
    return degrees * PI / 180;
}
