#include "Item.h"


Item::Item(const std::string& name, float x, float y)
	:name(name)
{
	setPosition(x, y);
}

void Item::draw(sf::RenderWindow& window) const
{
	window.draw(sprite);
}

void Item::update(float deltaTime)
{
	sprite.setPosition(position.x, position.y);
}

void Item::setSprite(const sf::Sprite& s)
{
	sprite = s;
}

const std::string& Item::getName() const
{
	return name;
}

void Item::setName(const std::string& name)
{
	this->name = name;
}
