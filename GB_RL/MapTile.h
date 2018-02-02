#pragma once

//#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
//#include "Item.h"
#include <stack>

class Map;
class Item;
class Character;

class MapTile
{
public:
	MapTile( Map* parent = nullptr);
	MapTile( const MapTile& other);
	MapTile& operator=(const MapTile& other);

	const sf::Vector2i& getGridPos() const;
	const sf::Vector2f& getWorldPos() const;
	const sf::Sprite& getSprite() const;

	void setGridPos(const sf::Vector2i& pos);
	void setWorldPos(const sf::Vector2f& pos);
	void setSprite(const sf::Sprite& sprite);

	void draw( sf::RenderWindow& window);
	void update( float deltaTime );

	void setOccupier( Character* occupier);
	Character* getOccupier( );
	void addItem( Item* item );
	Item* removeItem();
	Item* removeSpecifiedItem( const std::string& itemName );
	std::vector<Item*>& getItems();

	void addNeighbor( MapTile* n);
	std::vector<MapTile* >& getNeighbors();

	void setColor( const sf::Color& color);

	Map* getParent() const;
	void setParent(Map* m);
	bool canBeEntered();
	
	bool isWall() const;
	void setIsWall(bool wall);
	int getCost() const;

private:
	sf::Vector2i gridPos;
	sf::Vector2f worldPos;

	sf::Sprite mapSprite;

	Character* currentOccupier = nullptr;
	std::vector<Item*> items;

	std::vector<MapTile* > neighbors;
	Map* parent;

	bool wall = false;
	int costToEnter = 1;
};
