#include "GameObject.h"
#include "Utilities.h"

void GameObject::Update()
{
	Move();
}

void GameObject::Move()
{
	position.x += speed.x;
	position.y += speed.y;

	float width = (float)GetScreenWidth();
	float height = (float)GetScreenHeight();

	if (position.x > width)
		position.x -= width;
	else if (position.x < 0)
		position.x += width;

	if (position.y > height)
		position.y -= height;
	else if (position.y < 0)
		position.y += height;
}

void GameObject::Draw()
{
	Utilities::DrawTextureExCustom(sprite, position, rotation, 1.f, WHITE);
}
