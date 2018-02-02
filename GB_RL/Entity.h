#pragma once
#include <SFML/System/Vector2.hpp>

class Entity
{
public:
	Entity();
	const sf::Vector2f& getPosition() const;
	float getX() const;
	float getY() const;

	void setPosition( float x, float y);
	void setPosition( const sf::Vector2f& pos );

	void translate(float deltaX, float deltaY);
	void translate( const sf::Vector2f& delta );

protected:
	sf::Vector2f position;

};
