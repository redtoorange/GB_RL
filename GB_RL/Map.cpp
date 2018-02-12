#include "Map.h"
#include "MapGenerator.h"
#include <iostream>
#include "AssetManager.h"

Map::Map()
{
}

Map::Map(int width, int height, const sf::Texture& spriteSheet)
{
	generateMap(width, height, spriteSheet);
}


MapTile* Map::getFreeTile()
{
	bool found = false;
	int tries = 0;

	while( tries++ < 1000)
	{
		int x = randInt(0, width);
		int y = randInt(0, height);

		if( !tileMap[x][y].isWall() && tileMap[x][y].getOccupier() == nullptr)
				return &tileMap[x][y];
	}

	return nullptr;
}

Map::Map(const sf::Texture& spriteSheet, AssetManager& manager)
	:validRenderState(false)
{
	state.texture = &spriteSheet;
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
//				tileMap[x][y].setSprite(sf::Sprite{spriteSheet, {0 * SPRITE_WIDTH, 1 * SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT}});
				tileMap[x][y].setSprite(sf::Sprite{*manager.getTexture("floor")});
			}
			else if( map[x][y] == static_cast<char>(WALL))
			{
//				tileMap[x][y].setSprite(sf::Sprite{spriteSheet, {1 * SPRITE_WIDTH, 1 * SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT}});
				tileMap[x][y].setSprite(sf::Sprite{*manager.getTexture("wall")});
				tileMap[x][y].setIsWall(true);
			}
			else if( map[x][y] == static_cast<char>(CLOSED_DOOR))
			{
//				tileMap[x][y].setSprite(sf::Sprite{spriteSheet, {5 * SPRITE_WIDTH, 2 * SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT}});
				tileMap[x][y].setSprite(sf::Sprite{*manager.getTexture("door")});
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

void Map::createVertexArray( const sf::FloatRect& viewRect)
{
	for( auto& batch : renderBatches )
	{
		batch.second.clear();
	}


	sf::VertexArray* verts = nullptr;
	
	bool initial = false;

	for( int x = 0; x < width; x++)
	{
		for( int y = 0; y < height; y++)
		{
			const MapTile* tile =  &tileMap[x][y];
			const sf::Sprite& s = tile->getSprite();
			sf::FloatRect bound = s.getGlobalBounds();

			if( tile->getVisibility() != Visibility::VISIBLE || bound.intersects(viewRect) ) continue;

			sf::Vertex quad[4];

			
			
			const sf::Texture* t = s.getTexture();

			auto iter = renderBatches.find(t);
			if( iter == renderBatches.end() )
			{
				std::cout << "Created a new Vertext Array for a texture\n";
				renderBatches.emplace(t, sf::VertexArray(sf::Quads));
				iter = renderBatches.find(t);
			}
			verts = &iter->second;

			
			auto trect = s.getTextureRect();

			quad[0].position = sf::Vector2f(bound.left, bound.top);
			quad[1].position = sf::Vector2f(bound.left + bound.width, bound.top);
			quad[2].position = sf::Vector2f(bound.left + bound.width, bound.top + bound.height);
			quad[3].position = sf::Vector2f(bound.left, bound.top + bound.height);

			quad[0].texCoords = sf::Vector2f(trect.left, trect.top);
			quad[1].texCoords = sf::Vector2f(trect.left + trect.width, trect.top);
			quad[2].texCoords = sf::Vector2f(trect.left + trect.width, trect.top + trect.height);
			quad[3].texCoords = sf::Vector2f(trect.left, trect.top + trect.height);

			const sf::Color c = s.getColor();
			quad[0].color = c;
			quad[1].color = c;
			quad[2].color = c;
			quad[3].color = c;
	
			verts->append(quad[0]);
			verts->append(quad[1]);
			verts->append(quad[2]);
			verts->append(quad[3]);
		}
	}

	validRenderState = true;
}

void Map::drawMap(sf::RenderWindow& window)
{
//	if( !validRenderState ) 
//		createVertexArray();
//
//
//	window.getView().getViewport();
	createVertexArray( window.getView().getViewport() );
	for( auto& batch : renderBatches)
	{
		state.texture = batch.first;
		window.draw(batch.second, state);
	}



	// Draw fully visible
//	for( int x = 0; x < width; x++)
//	{
//		for( int y = 0; y < height; y++)
//		{
//			MapTile* tile = &tileMap[x][y];
//			Visibility vis = tile->getVisibility();
//
//			if( vis == Visibility::VISIBLE )
//			{
////				tile->setVisibility(Visibility::IN_SHADOW);
//				//Tile fully lit, render it
//				tile->draw( window );
//			}
////			else if( vis == Visibility::IN_SHADOW )
////			{
////				//Tile in shadow
////				// Add tile to shadow render batch
////				tile->draw( window );
////			}
////			else
////			{
////				//Tile Hidden, do NOT draw!
////				//tile->draw( window );
////			}
//		}
//	}

//	for( auto& batch : renderBatches)
//	{
//		state.texture = batch.first;
//		window.draw(batch.second, state);
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

void Map::invalidateTileBatches()
{
	validRenderState = false;
}
