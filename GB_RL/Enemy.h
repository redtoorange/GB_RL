#pragma once
#include "Character.h"

class EnemyCharacter : public Character
{
public:
	EnemyCharacter( const sf::Sprite& sprite, const std::string& name, Map* map, int x, int y);
	EnemyCharacter( const sf::Sprite& sprite, const std::string& name, MapTile* tile);
	virtual ~EnemyCharacter();

	void setManager(EnemyManager* manager);

	virtual int dealDamage() override;
	virtual void takeDamage(int amount) override;


	virtual void draw(sf::RenderWindow& window) const override;
private:
	EnemyManager* manager = nullptr;
};
