#include "Character.h"
#include "Map.h"
#include "EnemyManager.h"
#include <iostream>



Character::Character(const sf::Sprite& sprite, const std::string& name, Map* map, int x, int y)
	:sprite(sprite), name(name)
{
	this->sprite.setOrigin(16, 16);
	moveToTile(map->getTileByGrid(x, y), false);
}

Character::Character(const sf::Sprite& sprite, const std::string& name, MapTile* tile)
	:sprite(sprite), name(name), currentTile(tile)
{
	this->sprite.setOrigin(16, 16);
	
	moveToTile(tile, false);
}

void Character::draw(sf::RenderWindow& window) const
{
	window.draw(sprite);
}

void Character::update(float deltaTime)
{
	if( moving )
	{
		position = lerp(position, destination, .25f);
		if( abs(distance(position, destination)) < 0.05f )
		{
			position = destination;
			moving = false;
		}
	}
	sprite.setPosition(position.x, position.y);
}

void Character::setSprite(const sf::Sprite& s)
{
	sprite = s;
}

sf::Vector2i Character::getGridPos()
{
	sf::Vector2i pos;

	if( currentTile )
	{
		pos = currentTile->getGridPos();
	}

	return pos;
}


const std::string& Character::getName() const
{
	return name;
}


void Character::moveToTile(MapTile* tile, bool smooth)
{
	if( currentTile )
		currentTile->setOccupier(nullptr);

	currentTile = tile;
	
	if( currentTile)
	{
		currentTile->setOccupier(this);
		if( smooth )
		{
			destination = currentTile->getWorldPos();
			moving = true;
		}
		else
		{
			setPosition(currentTile->getWorldPos());
		}
	}
}

MapTile* Character::getTile()
{
	return currentTile;
}

int Character::dealDamage()
{
	return damage;
}

void Character::takeDamage(int amount)
{
	hp -= amount;
}


Character::~Character()
{
	if( currentTile )
		currentTile->setOccupier( nullptr );

	cout << "Character has been destroyed.\n";
}