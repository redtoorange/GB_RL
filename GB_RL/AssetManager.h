#pragma once

#include <SFML/Graphics.hpp>
#include "json.hpp"
using json = nlohmann::json;

enum AssetType
{
	PLAYER,
	ENEMY
};

enum PlayerClass : unsigned int
{
	ROGUE = 0,
	DRUID = 1,
	BARB = 2,
	GLAD = 3,
	RANGER = 4,
	KNIGHT = 5,
	MAGE = 6,
};

enum Enemy : unsigned int
{
	RAT = 0,
	T_SPIDER = 1,
	SALAMAND = 2,
	G_SPIDER = 3,
	FROG = 4,
	R_BEETLE = 5,
	M_PEDE = 6,
	SNEK = 7
};

class AssetManager
{
public:
	AssetManager();
	
	sf::Texture* getTexture();
	sf::IntRect getRect( AssetType type, int name );
	sf::Texture* getTexture( const std::string& name );

private:
	sf::Texture gameTexture;

	json enemy_sprites;
	json player_sprites;

	void readFile( const std::string& path, json& dest );
	sf::IntRect parseRect(json& data, const std::string& index);

	std::map<std::string, sf::Texture> textures;
};
