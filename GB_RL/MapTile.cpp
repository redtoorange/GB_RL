﻿#include "MapTile.h"

#include "Item.h"
#include <iostream>

MapTile::MapTile( Map* parent)
	:parent(parent)
{
}

MapTile::MapTile(const MapTile& other)
	: gridPos(other.getGridPos()), worldPos(other.getWorldPos()), mapSprite(other.getSprite())
{
}

MapTile& MapTile::operator=(const MapTile& other)
{
	if( &other == this )
		return *this;

	mapSprite = other.getSprite();
	gridPos = other.getGridPos();
	worldPos = other.getWorldPos();

	return *this;
}


const sf::Vector2i& MapTile::getGridPos() const
{
	return gridPos;
}

const sf::Vector2f& MapTile::getWorldPos() const
{
	return worldPos;
}

const sf::Sprite& MapTile::getSprite() const
{
	return mapSprite;
}


void MapTile::setGridPos(const sf::Vector2i& pos)
{
	gridPos = pos;
}

void MapTile::setWorldPos(const sf::Vector2f& pos)
{
	worldPos = pos;
	mapSprite.setPosition( worldPos );
}

void MapTile::setSprite(const sf::Sprite& sprite)
{
	mapSprite = sprite;
	mapSprite.setPosition( worldPos );
	mapSprite.setOrigin(16, 16);
}

void MapTile::draw(sf::RenderWindow& window)
{
	window.draw(mapSprite);

	for( Item* i : items)
	{
		i->draw(window);
	}	
}


void MapTile::update(float deltaTime)
{
	for (Item* i : items)
	{
		i->update(deltaTime);
	}
}

void MapTile::setOccupier(Character* occupier)
{
	currentOccupier = occupier;
//	occupiers.push_back(occupier);
//	occupier->setPosition( worldPos );
}


void MapTile::addItem(Item* item)
{
	item->setPosition(worldPos);
	items.push_back(item);
}

Item* MapTile::removeItem()
{
	Item* item = nullptr;
	
	if( !items.empty() )
	{
		item = items.back();
		items.pop_back();
	}

	return item;
}

Item* MapTile::removeSpecifiedItem(const std::string& itemName)
{
	Item* item = nullptr;

	for( Item* i : items)
	{
		if(i->getName() == itemName )
		{
			item = i;
			break;
		}
	}

	return item;
}


void MapTile::addNeighbor(MapTile* n)
{
	neighbors.push_back(n);
}

std::vector<MapTile*>& MapTile::getNeighbors()
{
	return neighbors;
}


void MapTile::setColor( const sf::Color& color)
{
	mapSprite.setColor( color );
}


Map* MapTile::getParent() const
{
	return parent;
}

void MapTile::setParent(Map* m)
{
	parent = m;
}

bool MapTile::canBeEntered()
{
	return currentOccupier == nullptr && !wall;
}

void MapTile::setIsWall(bool wall)
{
	this->wall = wall;
}


Character* MapTile::getOccupier()
{
	return currentOccupier;
}


int MapTile::getCost() const
{
	if (currentOccupier)
		return costToEnter + 5;

	return costToEnter;
}

bool MapTile::isWall() const
{
	return wall;
}


std::vector<Item*>& MapTile::getItems()
{
	return items;
}
