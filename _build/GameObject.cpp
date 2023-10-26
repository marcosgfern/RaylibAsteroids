#include "GameObject.h"
#include "Utilities.h"

GameObject::GameObject()
{
	position = Vector2();
	speed = Vector2();
	radius = 0;
	rotation = 0.f;
	active = true;

	sprite = Texture2D();
}

Vector2 GameObject::GetPosition()
{
	return position;
}

float GameObject::GetRadius()
{
	return radius;
}

bool GameObject::IsActive()
{
	return active;
}

void GameObject::SetActive(bool value)
{
	active = value;
}

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
