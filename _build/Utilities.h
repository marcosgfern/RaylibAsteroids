#include "raylib.h"

class Utilities
{
public:
	static void DrawTextureExCustom(Texture2D texture, Vector2 position, float rotation, float scale, Color tint);
	static Vector2 RandomNormalizedVector();
};