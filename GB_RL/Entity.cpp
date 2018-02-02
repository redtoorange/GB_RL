#include "Entity.h"

Entity::Entity()
{
}

const sf::Vector2f& Entity::getPosition() const
{
	return position;
}

float Entity::getX() const
{
	return position.x;
}

float Entity::getY() const
{
	return position.y;
}

void Entity::setPosition(float x, float y)
{
	position.x = x;
	position.y = y;
}

void Entity::setPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void Entity::translate(float deltaX, float deltaY)
{
	position.x += deltaX;
	position.y += deltaY;
}

void Entity::translate(const sf::Vector2f& delta)
{
	translate(delta.x, delta.y);
}
