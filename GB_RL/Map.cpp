#include "Map.h"
#include "MapGenerator.h"
#include <iostream>

Map::Map()
{
}

Map::Map(int width, int height, const sf::Texture& spriteSheet)
{
	generateMap(width, height, spriteSheet);
}


MapTile* Map::getFreeTile()
{
	for( int x = 0; x < width; x++)
	{
		for( int y = 0; y < height; y++)
		{
			if( !tileMap[x][y].isWall() && tileMap[x][y].getOccupier() == nullptr)
				return &tileMap[x][y];
		}
	}

	return nullptr;
}

Map::Map(const sf::Texture& spriteSheet)
{
	states.texture = &spriteSheet;
	MapGenerator generator{5, 5, 80, 80, 5, 10, 3, 10};
	auto map = generator.create();

	this->width = 80;
	this->height = 80;

	tileMap.resize(width);
	for( int i = 0; i < width; i++)
	{
		tileMap[i].resize(height);
	}

	for( int x = 0; x < width; x++)
	{
		for( int y = 0; y < height; y++)
		{
			tileMap[x][y].setParent(this);
			tileMap[x][y].setGridPos({x, y});
			tileMap[x][y].setWorldPos(sf::Vector2f(x * SPRITE_WIDTH, y * SPRITE_HEIGHT));

			if( map[x][y] == static_cast<char>(FLOOR))
			{
				tileMap[x][y].setSprite(sf::Sprite{spriteSheet, {0 * SPRITE_WIDTH, 1 * SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT}});
			}
			else if( map[x][y] == static_cast<char>(WALL))
			{
				tileMap[x][y].setSprite(sf::Sprite{spriteSheet, {1 * SPRITE_WIDTH, 1 * SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT}});
				tileMap[x][y].setIsWall(true);
			}
			else if( map[x][y] == static_cast<char>(CLOSED_DOOR))
			{
				tileMap[x][y].setSprite(sf::Sprite{spriteSheet, {5 * SPRITE_WIDTH, 2 * SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT}});
			}
				
		}
	}

	// constructor neighbor graph
	for( int x = 0; x < width; x++)
	{
		for( int y = 0; y < height; y++)
		{
			MapTile& current = tileMap[x][y];

			if( current.isWall() ) continue;

			// Up
			if( y > 0)
			{
				current.addNeighbor( &tileMap[x][y-1] );
			}

			// Up right
			if( y > 0 && x < width - 1 )
			{
				current.addNeighbor(&tileMap[x + 1][y - 1]);
			}

			// Up left
			if( y > 0 && x > 0)
			{
				current.addNeighbor(&tileMap[x - 1][y - 1]);
			}

			// Down
			if( y < height - 1)
			{
				current.addNeighbor( &tileMap[x][y+1] );
			}

			// Down left
			if (y < height - 1 && x > 0)
			{
				current.addNeighbor(&tileMap[x - 1][y + 1]);
			}

			// Down right
			if (y < height - 1 && x < width - 1)
			{
				current.addNeighbor(&tileMap[x + 1][y + 1]);
			}


			// Right
			if( x < width - 1)
			{
				current.addNeighbor( &tileMap[x+1][y] );
			}

			// Left
			if( x > 0)
			{
				current.addNeighbor( &tileMap[x-1][y] );
			}
		}
	}
}

void Map::generateMap(int width, int height, const sf::Texture& spriteSheet)
{
	// Allocate the tileMap array
	this->width = width;
	this->height = height;

	tileMap.resize(width);
	for( int i = 0; i < width; i++)
	{
		tileMap[i].resize(height);
	}

	// Build the maps
	for( int x = 0; x < width; x++)
	{
		for( int y = 0; y < height; y++)
		{
			tileMap[x][y].setParent(this);
			tileMap[x][y].setGridPos({x, y});
			tileMap[x][y].setWorldPos(sf::Vector2f(x * SPRITE_WIDTH, y * SPRITE_HEIGHT));

			if( x == 0 || y == 0 || x == width-1 || y == height-1)
			{
				// Other Wall
				tileMap[x][y].setSprite(sf::Sprite{spriteSheet, {1 * SPRITE_WIDTH, 1 * SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT}});
				tileMap[x][y].setIsWall(true);
			}
			else if( y == 1 && (x != 0 || x != width-1) )
			{
				if(x == width/2)
				{
					//Door
					tileMap[x][y].setSprite(sf::Sprite{spriteSheet, {5 * SPRITE_WIDTH, 2 * SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT}});
				}
				else
				{
					//Other Wall
					tileMap[x][y].setSprite(sf::Sprite{spriteSheet, {2 * SPRITE_WIDTH, 2 * SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT}});
				}
			}
			else
			{
				// Floor
				tileMap[x][y].setSprite(sf::Sprite{spriteSheet, {0 * SPRITE_WIDTH, 1 * SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT}});
			}
		}
	}

	// constructor neighbor graph
	for( int x = 0; x < width; x++)
	{
		for( int y = 0; y < height; y++)
		{
			MapTile& current = tileMap[x][y];

			// Up
			if( y > 0)
			{
				current.addNeighbor( &tileMap[x][y-1] );
			}

			// Up right
			if( y > 0 && x < width - 1 )
			{
				current.addNeighbor(&tileMap[x + 1][y - 1]);
			}

			// Up left
			if( y > 0 && x > 0)
			{
				current.addNeighbor(&tileMap[x - 1][y - 1]);
			}

			// Down
			if( y < height - 1)
			{
				current.addNeighbor( &tileMap[x][y+1] );
			}

			// Down left
			if (y < height - 1 && x > 0)
			{
				current.addNeighbor(&tileMap[x - 1][y + 1]);
			}

			// Down right
			if (y < height - 1 && x < width - 1)
			{
				current.addNeighbor(&tileMap[x + 1][y + 1]);
			}


			// Right
			if( x < width - 1)
			{
				current.addNeighbor( &tileMap[x+1][y] );
			}

			// Left
			if( x > 0)
			{
				current.addNeighbor( &tileMap[x-1][y] );
			}
		}
	}

	sf::Sprite cSprite;
	cSprite.setTexture( spriteSheet );
	cSprite.setTextureRect(sf::IntRect{0 * SPRITE_WIDTH, 4 * SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT});
	cSprite.setOrigin(16, 16);
	chest.setSprite(cSprite);
	chest.setName("Treasure Chest");

	tileMap[width/2][height/2].addItem(&chest);
}


void Map::updateTiles(float deltaTime)
{
	for( int x = 0; x < width; x++)
	{
		for( int y = 0; y < height; y++)
		{
			tileMap[x][y].update(deltaTime);
		}
	}
}

void Map::createVertexArray()
{
	verts.clear();
	verts.setPrimitiveType(sf::Quads);
	
	bool initial = false;

	for( int x = 0; x < width; x++)
	{
		for( int y = 0; y < height; y++)
		{
			sf::Vertex quad[4];

			const sf::Sprite& s = tileMap[x][y].getSprite();
			auto bound = s.getGlobalBounds();
			auto trect = s.getTextureRect();

			quad[0].position = sf::Vector2f(bound.left, bound.top);
			quad[1].position = sf::Vector2f(bound.left + bound.width, bound.top);
			quad[2].position = sf::Vector2f(bound.left + bound.width, bound.top + bound.height);
			quad[3].position = sf::Vector2f(bound.left, bound.top + bound.height);

			quad[0].texCoords = sf::Vector2f(trect.left, trect.top);
			quad[1].texCoords = sf::Vector2f(trect.left + trect.width, trect.top);
			quad[2].texCoords = sf::Vector2f(trect.left + trect.width, trect.top + trect.height);
			quad[3].texCoords = sf::Vector2f(trect.left, trect.top + trect.height);
	
			verts.append(quad[0]);
			verts.append(quad[1]);
			verts.append(quad[2]);
			verts.append(quad[3]);
		}
	}

	validRenderState = true;
}

void Map::drawMap(sf::RenderWindow& window)
{
	if( !validRenderState ) 
		createVertexArray();
//	sf::RectangleShape rectangle;
//	rectangle.setSize(sf::Vector2f(32, 32));
//	rectangle.setOrigin(16, 16);
//	
//	rectangle.setFillColor(sf::Color{0, 0, 0, 0});
//	
//	rectangle.setOutlineColor(sf::Color::Green);
//	rectangle.setOutlineThickness(-1);
//	sf::RenderStates states;
//
//
//	sf::Vertex quad[4];
//
//	sf::Sprite s;
//	auto bound = s.getGlobalBounds();
//	auto trect = s.getTextureRect();
//
//	quad[0].position = sf::Vector2f(bound.left, bound.top);
//	quad[1].position = sf::Vector2f(bound.left, bound.top+height);
//	quad[2].position = sf::Vector2f(bound.left + bound.width, bound.top+bound.height);
//	quad[3].position = sf::Vector2f(bound.left+bound.width, bound.top);
//
//	quad[0].texCoords = sf::Vector2f(trect.left, trect.top);
//	quad[1].texCoords = sf::Vector2f(trect.left, trect.top+height);
//	quad[2].texCoords = sf::Vector2f(trect.left + trect.width, trect.top+trect.height);
//	quad[3].texCoords = sf::Vector2f(trect.left+trect.width, trect.top);
//	
	//verts.append(quad);
	
//	states.transform = window.getView().getTransform();
	
//	window.draw(verts);
	window.draw(verts, states);


//	for( int x = 0; x < width; x++)
//	{
//		for( int y = 0; y < height; y++)
//		{
//			tileMap[x][y].draw( window );
//			//window.draw( tileMap[x][y].getSprite());
//
//			//rectangle.setPosition(tileMap[x][y].getWorldPos());
//			//window.draw(rectangle);
//		}
//	}
}

MapTile* Map::getTileByGrid(int x, int y)
{
	return &(tileMap[x][y]);
}


MapTile* Map::getTileByWorld(const sf::Vector2f& pos)
{
	MapTile* tile = nullptr;

	for( int x = 0; x < width && !tile; x++)
	{
		for( int y = 0; y < height && !tile; y++)
		{
			if( tileMap[x][y].getSprite().getGlobalBounds().contains(pos) )
				tile = &tileMap[x][y];
		}
	}

	return tile;
}
