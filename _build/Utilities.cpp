#include "Utilities.h"
#include "raylib.h"
#include "raymath.h"

#include <random>

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
    vector.y = rand() / static_cast<float>(RAND_MAX);

    return Vector2Normalize(vector);
}