#include "Player.h"
#include "Utilities.h"
#include "raymath.h"

static int TotalLifes = 3;

static int BaseSpeed = 5;
static int BaseRotationSpeed = 3;

Player::Player()
{
	lifes = TotalLifes;

	lastShotTimestamp = 0;

	position = Utilities::GetScreenCenter();
	speed = { 0.0f, 0.0f };
	radius = 10;
	rotation = 0.0f;
}

void Player::SetSprite(Texture2D newSprite)
{
	sprite = newSprite;
}

void Player::Reset()
{
	lifes = TotalLifes;

	lastShotTimestamp = 0;

	position = Utilities::GetScreenCenter();
	speed = { 0.0f, 0.0f };
	rotation = 0.0f;
}

void Player::SetSpeed(Vector2 rawDirection)
{
	speed = Vector2Scale(
		Vector2Normalize(rawDirection),
		BaseSpeed);
}
