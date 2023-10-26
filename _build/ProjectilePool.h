#pragma once

#include "Projectile.h"

#include <list>
#include <functional>

class ProjectilePool
{
private:
	std::list<Projectile> elements;

public:
	std::list<std::reference_wrapper<Projectile>> GetActiveElements();

	void AddElement(Vector2 startingPosition, float directionAngleInDegrees);
	void Clear();
};