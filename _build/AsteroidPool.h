#pragma once

#include "Asteroid.h"

#include <list>
#include <functional>

class AsteroidPool
{
private:
	std::list<Asteroid> elements;

public:
	std::list<std::reference_wrapper<Asteroid>> GetActiveElements();

	void AddElements(int quantity, int screenWidth, int screenHeight);
	void Clear();
};