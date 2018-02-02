﻿#pragma once
#include "Character.h"

class Map;

class Player : public Character
{
public:
	Player(const sf::Sprite& sprite, const std::string& name, Map* map, int x, int y);
	Player(const sf::Sprite& sprite, const std::string& name, MapTile* tile);


	virtual void draw(sf::RenderWindow& window) const override;
	virtual void update(float deltaTime) override;

	virtual int dealDamage() override;
	virtual void takeDamage(int amount) override;

	bool shouldEnemiesTick() const;
	void setEnemiesShouldTick( bool tick );

private:
	bool moved = false;
	bool enemiesShouldTick = false;

	float movementDelay = .25f;
	float delayRemaining = 0.0f;

	void movement( float deltaTime );
	void setup();
};