#include "Player.h"
#include "Utilities.h"
#include "raymath.h"

static int TotalLifes = 3;

static int BaseSpeed = 5;
static int BaseRotationSpeed = 5;

Player::Player()
{
	lifes = TotalLifes;

	hasTripleShot = false;
	shootCoolingCounter = 0;

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

	hasTripleShot = false;
	shootCoolingCounter = 0;

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

void Player::SetRotation(float rotationDirection)
{
	rotation += rotationDirection * BaseRotationSpeed;

	if (rotation > 180.f) rotation -= 360.f;
	if (rotation < -180.f) rotation += 360.f;
}

void Player::Update()
{
	GameObject::Update();
	if (shootCoolingCounter > 0) shootCoolingCounter--;
}

std::list<Projectile> Player::Shoot(int coolingFrames)
{
	shootCoolingCounter = coolingFrames;

	std::list<Projectile> newProjectiles = {};

	newProjectiles.push_back(Projectile(GetShootingPoint(), rotation+180 + 90.f));
	if (hasTripleShot)
	{
		newProjectiles.push_back(Projectile(GetShootingPoint(), rotation+180 + 90.f + 10.f));
		newProjectiles.push_back(Projectile(GetShootingPoint(), rotation+180 + 90.f - 10.f));
	}

	return newProjectiles;
}

bool Player::CanShoot()
{
	return shootCoolingCounter <= 0;
}

Vector2 Player::GetShootingPoint()
{
	Vector2 relativePoint = Vector2Rotate({ 0.f, (float)radius }, Utilities::DegreesToRadians(rotation+180));
	Vector2 absolutePoint = Vector2Add(position, relativePoint);
	return absolutePoint;
}