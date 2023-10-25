#include "Player.h"
#include "Utilities.h"
#include "raylib.h"
#include "raymath.h"

static int TotalLifes;

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

void Player::Reset()
{
	lifes = TotalLifes;

	lastShotTimestamp = 0;

	position = Utilities::GetScreenCenter();
	speed = { 0.0f, 0.0f };
	rotation = 0.0f;
}

void Player::Update()
{
	position.x += speed.x;
	position.y += speed.y;

	float width = (float)GetScreenWidth();
	float height = (float) GetScreenHeight();

	if (position.x > width)
		position.x -= width;
	else if (position.x < 0) 
		position.x += width;

	if (position.y > height)
		position.y -= height;
	else if (position.y < 0)
		position.y += height;
}

void Player::SetSpeed(Vector2 rawDirection)
{
	speed = Vector2Scale(
		Vector2Normalize(rawDirection),
		BaseSpeed);
}

void Player::Draw()
{
	DrawCircleV(position, radius, WHITE);
}
