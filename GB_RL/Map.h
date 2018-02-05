#pragma once

#include "Util.h"
#include <vector>
#include "MapTile.h"
#include "Item.h"

class AssetManager;

class Map
{
public:
	Map();
	Map( int width, int height, const sf::Texture& spriteSheet);
	Map( const sf::Texture& spriteSheet, AssetManager& manager);

	void generateMap( int width, int height, const sf::Texture& spriteSheet);

	void drawMap(sf::RenderWindow& window);
	void updateTiles(float deltaTime);

	MapTile* getTileByWorld( const sf::Vector2f& pos );
	MapTile* getTileByGrid( int x, int y);
	MapTile* getFreeTile();

	void invalidateTileBatches();

private:
	void createVertexArray();


	const int SPRITE_WIDTH = 32;
	const int SPRITE_HEIGHT = 32;

	int width;
	int height;

	std::vector< std::vector<MapTile>> tileMap;

	Item chest;

	std::map<const sf::Texture*, sf::VertexArray> renderBatches;
	std::map<const sf::Texture*, sf::VertexArray> shadowBatches;
	sf::RenderStates state;

	bool validRenderState = false;
};
