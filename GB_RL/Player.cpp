#include "Player.h"

#include "Map.h"
#include "MapTile.h"
#include <iostream>

Player::Player(const sf::Sprite& sprite, const std::string& name, Map* map, int x, int y)
	: Character(sprite, name, map, x, y)
{
	setup();
}

Player::Player(const sf::Sprite& sprite, const std::string& name, MapTile* tile)
	: Character(sprite, name, tile)
{
	setup();
}


void Player::setup()
{
	hp = 25;
	damage = 5;
	//calculateLOS();
}

void Player::draw(sf::RenderWindow& window) const
{
	Character::draw(window);
}

void Player::update(float deltaTime)
{
	movement(deltaTime);
	Character::update(deltaTime);
}

void Player::movement( float deltaTime )
{
	if( moved )
	{
		delayRemaining -= deltaTime;
		if( delayRemaining <= 0)
		{
			delayRemaining = 0.0f;
			moved = false;
		}
		else
		{
			return;
		}
	}

	sf::Vector2i deltaMove;
	if( sf::Keyboard::isKeyPressed(sf::Keyboard::W) )
	{
		deltaMove.y -= 1;
		moved = true;
	}
	else if( sf::Keyboard::isKeyPressed(sf::Keyboard::S) )
	{
		deltaMove.y += 1;
		moved = true;
	}

	else if( sf::Keyboard::isKeyPressed(sf::Keyboard::D) )
	{
		deltaMove.x += 1;
		moved = true;
	}
	else if( sf::Keyboard::isKeyPressed(sf::Keyboard::A) )
	{
		deltaMove.x -= 1;
		moved = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		enemiesShouldTick = true;
		delayRemaining = movementDelay;
		moved = true;
		return;
	}

	if( moved )
	{
		sf::Vector2i pos = getGridPos() + deltaMove;
		MapTile* attempted = currentTile->getParent()->getTileByGrid(pos.x, pos.y);
		if (attempted && attempted->canBeEntered())
		{
			moveToTile(attempted);
			calculateLOS();
			enemiesShouldTick = true;
		}
		else
		{
			Character* o = attempted->getOccupier();
			if( o )
			{
				std::cout << name << " deals " << dealDamage() << " damage to " << o->getName() << ".\n";
				o->takeDamage( dealDamage() );
				enemiesShouldTick = true;
			}
			else
			{
				std::cout << "Blocked by Wall\n";
			}
		}

		delayRemaining = movementDelay;
		//player.translate(delta);
	}
}

bool Player::shouldEnemiesTick() const
{
	return enemiesShouldTick;
}

void Player::setEnemiesShouldTick(bool tick)
{
	enemiesShouldTick = tick;
}

int Player::dealDamage()
{
	return Character::dealDamage();
}

void Player::takeDamage(int amount)
{
	Character::takeDamage(amount);
}

void Player::calculateLOS()
{
	Map* m = currentTile->getParent();

	int cX = currentTile->getGridPos().x;
	int cY = currentTile->getGridPos().y;

	for( int x = 0; x < 6; x++)
	{
		for( int y = 0; y < 6; y++)
		{
			MapTile* t = m->getTileByGrid(x-3, y-3);
			if( t )
			{
				t->setVisibility(Visibility::VISIBLE);
			}
		}
	}

}
