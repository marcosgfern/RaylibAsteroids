#pragma once

#include "GameObject.h"
#include "Projectile.h"
#include "raylib.h"

#include <list>

class Player : public GameObject
{
private:
	int lifes;

	bool hasTripleShot;
	int shootCoolingCounter;

public:
	Player();
	void SetSprite(Texture2D newSprite);
	void SetSpeed(Vector2 rawDirection);
	void SetRotation(float rotationDirection);

	void Reset();

	void Update();

	std::list<Projectile> Shoot(int coolingFrames);
	bool CanShoot();
	Vector2 GetShootingPoint();
};
