#include "raylib.h"

class Player
{
public:
	static Texture2D Sprite;

	static void SetSprite(Texture2D sprite);

private:
	int lifes;

	int lastShotTimestamp;

	Vector2 position;
	Vector2 speed;
	int radius;
	float rotation;

public:
	Player();

	void Reset();

	void SetSpeed(Vector2 rawDirection);

	void Update();

	void Draw();
};
