#include "Player.h"
#include "raylib.h"

Player::Player(int totalLifes, Vector2 startingPosition)
{
	lifes = totalLifes;

	lastShotTimestamp = 0;

	position = startingPosition;
	speed = { 0.0f, 0.0f };
	radius = 1;
	rotation = 0.0f;
}