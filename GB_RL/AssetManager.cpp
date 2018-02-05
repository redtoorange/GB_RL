#include "AssetManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

const char* ENEMY_PATH = "assets/enemy_sprites.json";
const char* PLAYER_PATH = "assets/player_sprites.json";
const char* TEXTURE_PATH = "assets/gbaTileSet.png";

std::string pClasses[] = { "rogue", "driud", "barb", "gladiator", "ranger", "knight", "mage" };
std::string enemies[] = { "rat", "tiny_spiders", "salamander", "giant_spider", "frog", "rhino_beetle", "millipede", "snek" };



AssetManager::AssetManager()
{
	readFile(ENEMY_PATH, enemy_sprites);
	readFile(PLAYER_PATH, player_sprites);

	gameTexture.loadFromFile(TEXTURE_PATH);

	sf::Texture temp;

	temp.loadFromFile("assets/wall/brick_gray_0.png");
	textures.emplace("wall", temp);

	temp.loadFromFile("assets/floor/cobble_blood_1_new.png");
	textures.emplace("floor", temp);

	temp.loadFromFile("assets/doors/closed_door.png");
	textures.emplace("door", temp);
}


sf::Texture* AssetManager::getTexture(const std::string& name)
{
	return &textures[name];
}

void AssetManager::readFile(const std::string& path, json& dest)
{
	sf::FileInputStream fis;
	fis.open(path);
	std::string data;

	std::stringstream stream;
	char d;
	sf::Int64 pos = fis.tell();
	while( fis.read( &d, sizeof(d) ) )
	{
		pos += sizeof(d);
		stream << d;

		fis.seek(pos);
	}

	stream >> dest;
}


sf::Texture* AssetManager::getTexture()
{
	return &gameTexture;
}

sf::IntRect AssetManager::getRect( AssetType type, int name )
{
	if( type == ENEMY)
	{
		return parseRect(enemy_sprites, enemies[name]);
	}
	else if (type == PLAYER)
	{
		return parseRect(player_sprites, pClasses[name]);
	}

	return {0, 0, 0, 0};
}


sf::IntRect AssetManager::parseRect(json& data, const std::string& index)
{
	int width = data["tile_width"];
	int height = data["tile_height"];

	int pos_x = data[index]["pos_x"];
	pos_x *= width;
	int pos_y = data[index]["pos_y"];
	pos_y *= height;

	//cout << "X: " << rect.left << "\nY: " << rect.top <<  "\nW: " << rect.width << "\nH: " << rect.height << endl;
	return 	sf::IntRect{ pos_x, pos_y, width, height };
}