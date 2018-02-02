#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
using namespace std;

class Map;
class Character;
class EnemyCharacter;
class Player;

class EnemyManager
{
public:

	EnemyManager( Map* tileMap = nullptr, Player* player = nullptr);
	void setMap( Map* tileMap);
	void setPlayer( Player* player );

	void tick();
	void update(float delta);
	void draw(sf::RenderWindow& window);

	void addEnemy( EnemyCharacter* enemy );
	void moveTowardPlayer( EnemyCharacter* enemy);
	void removeEnemy( EnemyCharacter* enemy);

private:
	Map* tileMap = nullptr;
	Player* player = nullptr;

	vector<unique_ptr<EnemyCharacter>> enemies;
};
