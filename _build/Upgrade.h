#pragma once

#include "GameObject.h"
#include "Utilities.h"

class Upgrade : public GameObject
{
private:
	int activeTimeCounter;

public:
	Upgrade();
	void SetActive(bool value);

	void Respawn();

	void Update();

	void Draw();
};