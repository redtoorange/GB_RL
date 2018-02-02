#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>

class Item : public Entity
{
public:
	Item(const std::string& name = "No name", float x = 0, float y = 0);

	void draw(sf::RenderWindow& window) const;
	void update(float deltaTime);

	void setSprite(const sf::Sprite& s);

	const std::string& getName() const;
	void setName(const std::string& name );

protected:
	sf::Sprite sprite;
	std::string name;
};
