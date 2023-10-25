#include "Player.h"
#include "Utilities.h"
#include "raylib.h"

static int TotalLifes;

Player::Player()
{
	lifes = TotalLifes;

	lastShotTimestamp = 0;

	position = Utilities::GetScreenCenter();
	speed = { 0.0f, 0.0f };
	radius = 10;
	rotation = 0.0f;
}

void Player::Reset()
{
	lifes = TotalLifes;

	lastShotTimestamp = 0;

	position = Utilities::GetScreenCenter();
	speed = { 0.0f, 0.0f };
	rotation = 0.0f;
}

void Player::Draw()
{
	DrawCircleV(position, radius, WHITE);
}
