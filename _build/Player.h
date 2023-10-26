#pragma once

#include "GameObject.h"
#include "Projectile.h"
#include "ProjectilePool.h"
#include "raylib.h"

#include <list>

class Player : public GameObject
{
private:
	int lifes;

	bool hasTripleShot;
	int shootCoolingCounter;
	int invincibilityCounter;

	ProjectilePool* projectilePoolPointer;

public:
	Player();
	void SetSprite(Texture2D newSprite);
	void SetSpeed(Vector2 rawDirection);
	void SetRotation(float rotationDirection);

	void SetProjectilePool(ProjectilePool* poolPointer);

	void Reset();

	void Update();

	bool Hit();
	bool IsInvincible();

	void Shoot(int coolingFrames);
	bool CanShoot();
	Vector2 GetShootingPoint();
};
