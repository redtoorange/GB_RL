#pragma once
#include "Util.h"

#include <random>
#include <algorithm>

struct Room
{
	Room(int x, int y, int width, int height, int cellx, int celly);

	int x;
	int y;
	int width;
	int height;
	int cellx;
	int celly;

	std::vector<Room*> connections;

	
};

enum Terrain : char{
	FLOOR = '.',
    WALL = '#',
    CLOSED_DOOR = '+',
    OPEN_DOOR = '/',
    EMPTY_SPACE = '_',
    LIQUID = '~',
    ENTRANCE = '<',
    EXIT = '>'
};

class Magnitude 
{
public:
    sf::Vector2i dir;
    int distance;

    Magnitude(sf::Vector2i dir, int distance) 
		:dir(dir), distance(distance)
	{
    }
};

class MapGenerator
{
public:
	MapGenerator(int horizontalRooms, int verticalRooms, int dungeonWidth, int dungeonHeight,
                                    int minRoomWidth, int maxRoomWidth, int minRoomHeight, int maxRoomHeight);

	std::vector<std::vector<Terrain>> create();

private:
	int horizontalRooms, verticalRooms, dungeonWidth, dungeonHeight,
            minRoomWidth, maxRoomWidth, minRoomHeight, maxRoomHeight;

	std::vector<std::vector<Room>> rooms;
	std::vector<std::vector<Terrain>> map;
	std::vector<std::vector<char>> dungeon;

	void initRooms();
	void connectRooms();
	void connectUnconnectedRooms();
	void fullyConnect();
	void createRooms();
	void createCorridors();

	void digPath(sf::Vector2i start, sf::Vector2i end);
	sf::Vector2i randomWallPosition(Room* room, sf::Vector2i dir);

	bool contains( Room* a, Room* b);
	sf::Vector2i opposite( const sf::Vector2i& dir);

	std::random_device rd;
    std::mt19937 g;
};

