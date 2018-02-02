#include "EnemyManager.h"
#include <iostream>
#include "PathFinder.h"
#include "MapTile.h"

#include "Enemy.h"
#include "Player.h"


EnemyManager::EnemyManager(Map* tileMap, Player* player)
	:tileMap(tileMap), player(player)
{
}

void EnemyManager::tick()
{
	for( auto& e : enemies)
	{
		moveTowardPlayer( e.get() );
	}
}

void EnemyManager::moveTowardPlayer( EnemyCharacter* enemy)
{
	if( !player || !tileMap) return;

	vector<MapTile*> currentPath;
	sf::Vector2i pPos = player->getGridPos();
	sf::Vector2i ePos = enemy->getGridPos();


	currentPath = PathFinder::findPath( tileMap, enemy->getTile(), player->getTile());


	if(currentPath.size() >= 2)
	{

		MapTile* attempted = currentPath[1];

		if (attempted && attempted->canBeEntered())
		{
			enemy->moveToTile(attempted);
		}
		else
		{
			Character* other = attempted->getOccupier();
			if (other)
			{
				if(other == player)
				{
					int amount = enemy->dealDamage();

					cout << enemy->getName() << " deals " << amount << " damage to " << other->getName() << ".\n";
					other->takeDamage(amount);
				}
			}
		}
	}


}

void EnemyManager::update(float delta)
{
	for( auto& e : enemies)
	{
		e->update(delta);
	}
}

void EnemyManager::draw(sf::RenderWindow& window)
{
	for( auto& e : enemies)
	{
		e->draw(window);
	}
}

void EnemyManager::addEnemy(EnemyCharacter* enemy)
{
	enemy->setManager( this );
	enemies.emplace_back( enemy );
}

void EnemyManager::setMap(Map* tileMap)
{
	this->tileMap = tileMap;
}

void EnemyManager::setPlayer(Player* player)
{
	this->player = player;
}


void EnemyManager::removeEnemy(EnemyCharacter* enemy)
{
	for(auto iter = enemies.begin(); iter != enemies.end(); ++iter)
	{
		if( enemy == iter->get())
		{
			enemies.erase(iter);
			return;
		}
	}

	cout << "Enemy not found";
	
}
