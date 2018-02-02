#pragma once
#include "Entity.h"
#include "Util.h"

class EnemyManager;
class MapTile;
class Map;

class Character : public Entity
{
public:
	Character( const sf::Sprite& sprite, const std::string& name, Map* map, int x, int y);
	Character( const sf::Sprite& sprite, const std::string& name, MapTile* tile);
	virtual ~Character();

	virtual void draw( sf::RenderWindow& window ) const;
	virtual void update( float deltaTime );

	void setSprite( const sf::Sprite& s );
	sf::Vector2i getGridPos();

	MapTile* getTile();
	void moveToTile( MapTile* tile, bool smooth = true);

	const std::string& getName() const;

	virtual int dealDamage();
	virtual void takeDamage( int amount );

protected:
	int hp = 10;
	int damage = 1;

	sf::Sprite sprite;
	std::string name;

	MapTile* currentTile = nullptr;

	bool moving = false;
	sf::Vector2f source;
	sf::Vector2f destination;
};


