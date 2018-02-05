#include "GameScreen.h"

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include <memory>
#include <iostream>
using namespace std;



GameScreen::GameScreen(Game* game)
	:Screen(game), gb_view({ GB_WINDOW_WIDTH, GB_WINDOW_HEIGHT }, sf::Vector2f{ 0, 0 }, sf::Vector2f(GB_WINDOW_WIDTH, GB_WINDOW_HEIGHT))
{

	// Make the map
	tileMap = make_unique<Map>( *asset_manager.getTexture(), asset_manager);
	

	// Create some people for the map
	player = make_unique<Player>( sf::Sprite{ *asset_manager.getTexture(), asset_manager.getRect(PLAYER, KNIGHT) }, "Player", tileMap->getFreeTile() );
	
	enemy_manager.setMap(tileMap.get());
	enemy_manager.setPlayer( player.get() );
	enemy_manager.addEnemy( new EnemyCharacter({ *asset_manager.getTexture(), asset_manager.getRect(ENEMY, RAT) }, "Rat", tileMap->getFreeTile()));
	enemy_manager.addEnemy( new EnemyCharacter({ *asset_manager.getTexture(), asset_manager.getRect(ENEMY, T_SPIDER) }, "Tiny Spider", tileMap->getFreeTile()));

	gb_view.setCenter(player->getPosition());
}

GameScreen::~GameScreen()
{
	std::cout << "Deleted GameScreen\n";
}

void GameScreen::show()
{
}


void GameScreen::update(float deltaTime)
{
	player->update(deltaTime);
	if( player->shouldEnemiesTick() )
	{
		enemy_manager.tick();
		player->setEnemiesShouldTick( false );
	}
	enemy_manager.update(deltaTime);
	tileMap->updateTiles(deltaTime);

	gb_view.setTarget(player->getPosition());
	gb_view.update(deltaTime);
}

void GameScreen::draw(sf::RenderWindow& window)
{
	
	window.setView(gb_view.getView());

	// Draw stuff
	tileMap->drawMap( window );
	enemy_manager.draw(window);
	player->draw( window );
}

void GameScreen::hide()
{
}

void GameScreen::resized(float width, float height)
{
	gb_view.resized( static_cast<unsigned>(width), static_cast<unsigned>(height) );
}

CameraManager* GameScreen::getCamameraManager()
{
	return &gb_view;
}

void GameScreen::handleEvent(sf::Event& event)
{
	//Handle the events for the screen
	if (event.type == sf::Event::Resized)
	{
		resized(static_cast<float>(event.size.width), static_cast<float>(event.size.height));
	}

	if( event.type == sf::Event::MouseButtonPressed)
	{
		cout << "Mouse Clicked!" << endl;
		if( event.mouseButton.button == sf::Mouse::Left )
		{
			auto worldPos = game->getRenderWindow().mapPixelToCoords({event.mouseButton.x, event.mouseButton.y });
			cout << "Clicked: " << worldPos.x << "\t" << worldPos.y << endl;
			cout << "Player:  " << player->getPosition().x << "\t" << player->getPosition().x << endl;

			auto clickedTile = tileMap->getTileByWorld( worldPos );
			if(clickedTile )
			{
				if(clickedTile->getOccupier())
				{
					cout << "Tile occupied by " << clickedTile->getOccupier()->getName() << endl;
				}
				else
				{
					cout << "Tile has no occupier." << endl;
				}
				cout << "Tile Contains: ";
				for( auto i : clickedTile->getItems())
				{
					cout << i->getName() << ", ";
				}
				cout << endl;
			}
			else
			{
				cout << "No Tile Clicked." << endl;
			}
				
		}
		else if( event.mouseButton.button == sf::Mouse::Middle )
		{
			cout << "Middle!" << endl;
		}
		else if( event.mouseButton.button == sf::Mouse::Right )
		{
			cout << "Right!" << endl;
		}
	}
}
