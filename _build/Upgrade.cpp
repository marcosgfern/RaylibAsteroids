#include "Upgrade.h"

static float BaseSpeed = 4.f;
static float ActiveTimeInFrames = 600;

Upgrade::Upgrade()
	:GameObject()
{
	position = Utilities::RandomBorderSpawn();
	speed = Vector2Scale(Utilities::RandomNormalizedVector(), BaseSpeed);
	radius = 15;

	activeTimeCounter = 0;
}

void Upgrade::SetActive(bool value)
{
	GameObject::SetActive(value);
	activeTimeCounter = ActiveTimeInFrames * value;
}

void Upgrade::Respawn()
{
	active = true;
	activeTimeCounter = ActiveTimeInFrames;

	position = Utilities::RandomBorderSpawn();
	speed = Vector2Scale(Utilities::RandomNormalizedVector(), BaseSpeed);
}

void Upgrade::Update()
{
	if (active)
	{
		if (activeTimeCounter <= 0)
		{
			active = false;
		}
		else
		{
			GameObject::Update();
			activeTimeCounter--;
		}
	}
	
}

void Upgrade::Draw()
{
	if (active)
	{
		GameObject::Draw();
	}
}
