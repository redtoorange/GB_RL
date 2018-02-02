#include "Enemy.h"

#include "EnemyManager.h"
#include <iostream>

EnemyCharacter::EnemyCharacter(const sf::Sprite& sprite, const std::string& name, Map* map, int x, int y)
	:Character(sprite, name, map, x, y)
{
}

EnemyCharacter::EnemyCharacter(const sf::Sprite& sprite, const std::string& name, MapTile* tile)
	:Character(sprite, name, tile)
{
}

void EnemyCharacter::setManager(EnemyManager* manager)
{
	this->manager = manager;
}

int EnemyCharacter::dealDamage()
{
	return Character::dealDamage();
}

void EnemyCharacter::takeDamage(int amount)
{
	Character::takeDamage(amount);

	if( hp <= 0 && manager)
	{
		std::cout << name << " has died...\n";
		manager->removeEnemy(this);
	}
}

EnemyCharacter::~EnemyCharacter()
{
	std::cout << "Enemy Destroyed\n";
}
