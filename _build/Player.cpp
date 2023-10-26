#include "Player.h"
#include "Utilities.h"
#include "raymath.h"

static int TotalLifes = 3;

static int BaseSpeed = 5;
static int BaseRotationSpeed = 5;

static float InvincibilityTimeInSeconds = 2.f;

Player::Player()
	:GameObject()
{
	lifes = TotalLifes;

	hasTripleShot = false;
	shootCoolingCounter = 0;
	invincibilityCounter = 0;

	position = Utilities::GetScreenCenter();
	radius = 10;

	projectilePoolPointer = { 0 };
}

void Player::SetSprite(Texture2D newSprite)
{
	sprite = newSprite;
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

void Player::SetProjectilePool(ProjectilePool* poolPointer)
{
	projectilePoolPointer = poolPointer;
}

void Player::Reset()
{
	lifes = TotalLifes;

	hasTripleShot = false;
	shootCoolingCounter = 0;
	invincibilityCounter = 0;

	position = Utilities::GetScreenCenter();
	speed = { 0.0f, 0.0f };
	rotation = 0.0f;
}

void Player::Update()
{
	GameObject::Update();
	if (shootCoolingCounter > 0) shootCoolingCounter--;
	if (invincibilityCounter > 0) invincibilityCounter--;
}

void Player::Draw()
{
	if (IsInvincible()) Utilities::DrawTextureExCustom(sprite, position, rotation, 1.f, GRAY);
	else GameObject::Draw();
}

bool Player::Hit()
{
	if (!IsInvincible())
	{
		lifes--;
		if (lifes <= 0) return true;
		else invincibilityCounter = 60 * InvincibilityTimeInSeconds;
	}
}

bool Player::IsInvincible()
{
	return invincibilityCounter > 0;
}

void Player::Shoot(int coolingFrames)
{
	shootCoolingCounter = coolingFrames;

	std::list<Projectile> newProjectiles = {};

	projectilePoolPointer->AddElement(GetShootingPoint(), rotation+180 + 90.f);
	if (hasTripleShot)
	{
		projectilePoolPointer->AddElement(GetShootingPoint(), rotation+180 + 90.f + 10.f);
		projectilePoolPointer->AddElement(GetShootingPoint(), rotation+180 + 90.f - 10.f);
	}
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
