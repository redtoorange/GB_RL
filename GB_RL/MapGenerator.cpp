#include "MapGenerator.h"
#include <iostream>

using namespace std;

Room::Room(int x, int y, int width, int height, int cellx, int celly)
	: x(x),
		y(y),
		width(width),
		height(height),
		cellx(cellx),
		celly(celly)
{
}

vector<vector<Terrain>> MapGenerator::create()
{
	map.clear();
	rooms.clear();

	initRooms();
    connectRooms();
    connectUnconnectedRooms();
    fullyConnect();
    createRooms();
    createCorridors();

	return map;
}


void MapGenerator::initRooms()
{
	rooms.resize(horizontalRooms);
	map.resize(dungeonWidth);

	for(int x = 0; x < horizontalRooms; x++)
	{
		for(int y = 0; y < verticalRooms; y++)
		{
			rooms[x].emplace_back(0, 0, 0, 0, x, y);
		}	
	}

	for(int x = 0; x < dungeonWidth; x++)
	{
		for(int y = 0; y < dungeonHeight; y++)
		{
			map[x].emplace_back( Terrain::WALL );
		}	
	}
}

void MapGenerator::connectRooms()
{
	vector<Room*> unconnected;
	for(int x = 0; x < horizontalRooms; x++)
	{
		for(int y = 0; y < verticalRooms; y++)
		{
			unconnected.push_back(&rooms[x][y]);
		}	
	}
	random_shuffle(unconnected.begin(), unconnected.end());

	vector<sf::Vector2i> dirToCheck = {UP, DOWN, LEFT, RIGHT}; 

	for( Room* room : unconnected)
	{
		random_shuffle(dirToCheck.begin(), dirToCheck.end());
		for(auto& dir : dirToCheck)
		{
			int nextX = room->x + dir.x;
			int nextY = room->y + dir.y;
			if (nextX < 0 || nextX >= horizontalRooms || nextY < 0 || nextY >= verticalRooms) {
                    continue;
            }

			Room* otherRoom = &rooms[nextX][nextY];
			if( contains(room, otherRoom) )
			{
				break;
			}

			if( !otherRoom->connections.empty())
			{
				room->connections.push_back(otherRoom);
				break;
			}
		}
		
	}
}

void MapGenerator::connectUnconnectedRooms()
{
	for (int x = 0; x < horizontalRooms; x++) 
	{
        for (int y = 0; y < verticalRooms; y++)
		{
			Room* room = &rooms[x][y];

			if( room->connections.empty())
			{
				vector<sf::Vector2i> dirToCheck = {UP, DOWN, LEFT, RIGHT}; 
				random_shuffle(dirToCheck.begin(), dirToCheck.end());

				bool validRoom = false;
				Room* otherRoom = nullptr;

				int i = 0;
				do 
				{
					sf::Vector2i dir = dirToCheck[i++];

					int nextX = x + dir.x;
					if (nextX < 0 || nextX >= horizontalRooms) 
					{
						continue;
					}
					int nextY = y + dir.y;
					if (nextY < 0 || nextY >= verticalRooms) 
					{
						continue;
					}

					otherRoom = &rooms[nextX][nextY];
					validRoom = true;

					if (contains(otherRoom, room)) 
					{
						validRoom = false;
					}
					else 
					{
						break;
					}
                } 
				while (i < 4);

                if (validRoom) 
				{
                    room->connections.push_back(otherRoom);
                }
			}
		}
	}
}

void MapGenerator::fullyConnect()
{
	bool allGood;

	do
	{
		vector<Room*> deq;
		for (int x = 0; x < horizontalRooms; x++) 
		{
            for (int y = 0; y < verticalRooms; y++) 
			{
                deq.push_back(&rooms[x][y]);
            }
        }

		vector<Room*> connected;
		connected.push_back(deq.front());
		deq.erase(deq.begin());
		bool changed = true;

		testing:
		while(changed)
		{
			changed = false;
			for (Room* test : deq) {
                for (Room* r : connected) {
                    if ( contains(test, r)  || contains(r, test)) {
                        connected.push_back(test);

						auto it = find(deq.begin(), deq.end(), test);
						if( it != deq.end())
							deq.erase(it);

                        changed = true;
                        goto testing;
                    }
                }
            }
		}

		allGood = true;
        if (!deq.empty()) {
			vector<sf::Vector2i> dirToCheck = {UP, DOWN, LEFT, RIGHT}; 

            for (Room* room : deq) 
			{
                for (auto& dir : dirToCheck) {
                    int x = room->cellx + dir.x;
                    int y = room->celly + dir.y;
                    if (x >= 0 && y >= 0 && x < horizontalRooms && y < verticalRooms) {
                        Room* otherRoom = &rooms[x][y];
                        if ( find(connected.begin(), connected.end(), otherRoom) !=  connected.end() ) {
                            room->connections.push_back(otherRoom);
                            allGood = false;
                            goto doneTesting;
                        }
                    }
				}
            }
        }
		doneTesting:
		cout << "";
	}
	while (!allGood);
}

void MapGenerator::createRooms()
{
	int cwp = dungeonWidth / horizontalRooms;
    int chp = dungeonHeight / verticalRooms;
	Room* otherRoom;

	for (int x = 0; x < horizontalRooms; x++) 
	{
        for (int y = 0; y < verticalRooms; y++) 
		{
			int sx = cwp * x;
            int sy = chp * y;

            sx = max(sx, 2);
            sy = max(sy, 2);

			int roomw = randInt(minRoomWidth, maxRoomWidth + 1);
			int roomh = randInt(minRoomHeight, maxRoomHeight + 1);

			if( y > 0)
			{
				otherRoom = &rooms[x][y-1];
				while( sy - (otherRoom->y + otherRoom->height) < 3)
				{
					sy++;
				}
			}

			if( x > 0)
			{
				otherRoom = &rooms[x-1][y];
				while( sx - (otherRoom->x + otherRoom->width) < 3)
				{
					sx++;
				}
			}

			int sxOffset = round( nextInt(cwp - roomw) / 2.0f);
			int syOffset = round( nextInt(chp - roomh) / 2.0f);

			while( sx + sxOffset + roomw >= dungeonWidth)
			{
				if(sxOffset > 0)
					sxOffset--;
				else
					roomw--;
			}

			while( sy + syOffset + roomh >= dungeonHeight)
			{
				if(syOffset > 0)
					syOffset--;
				else
					roomh--;
			}

			sx += sxOffset;
			sy += syOffset;

			Room* r = &rooms[x][y];
			r->x = sx;
			r->y = sy;
			r->width = roomw;
			r->height = roomh;

			for (int xx = sx; xx < sx + roomw; xx++) 
			{
                for (int yy = sy; yy < sy + roomh; yy++) 
				{
                    map[xx][yy] = FLOOR;
                }
            }
		}
	}
}

sf::Vector2i getCardinalDirection(int x, int y) {
	sf::Vector2i Cardinals[] = {UP, DOWN, LEFT, RIGHT};
    if (x == 0 && y == 0) {
        return {0, 0};
    }

    int absx = abs(x);

    if (y > absx) {
        return UP;
    }

    int absy = abs(y);

    if (absy > absx) {
        return DOWN;
    }

    if (x > 0) {
        if (-y == x) {//on diagonal
            return DOWN;
        }
        return RIGHT;
    }

    if (y == x) {//on diagonal
        return UP;
    }
    return LEFT;

}


void MapGenerator::digPath(sf::Vector2i start, sf::Vector2i end) {
    int xOffset = end.x - start.x;
    int yOffset = end.y - start.y;
    int xpos = start.x;
    int ypos = start.y;

    vector<Magnitude> moves;

    int xAbs = abs(xOffset);
    int yAbs = abs(yOffset);

    double firstHalf = nextInt(100)/100.f;
    double secondHalf = 1 - firstHalf;

    sf::Vector2i xDir = xOffset < 0 ? LEFT : RIGHT;
    sf::Vector2i yDir = yOffset > 0 ? DOWN : UP;

    if (xAbs < yAbs) {
        int tempDist = ceil(yAbs * firstHalf);
        moves.emplace_back( yDir, tempDist);
        moves.emplace_back( xDir, xAbs);
        tempDist = floor(yAbs * secondHalf);
        moves.emplace_back( yDir, tempDist);
    } else {
        int tempDist = ceil(xAbs * firstHalf);
        moves.emplace_back( xDir, tempDist);
        moves.emplace_back( yDir, yAbs);
        tempDist = floor(xAbs * secondHalf);
        moves.emplace_back( xDir, tempDist);
    }

    map[xpos][ypos] = FLOOR;

    while (!moves.empty()) {
        Magnitude move = moves.front();
		moves.erase(moves.begin());

        sf::Vector2i dir = move.dir;
        int dist = move.distance;

        while (dist > 0) 
		{
            xpos += dir.x;
            ypos += dir.y;
            map[xpos][ypos] = FLOOR;
            dist--;
        }
    }
}

sf::Vector2i MapGenerator::randomWallPosition(Room* room, sf::Vector2i dir) {
    int x, y;

    if( dir == LEFT )
    {
	    y = randInt(room->y + 1, room->y + room->height);
        x = room->x - 1;
        map[x][y] = CLOSED_DOOR;
		return {x - 1, y};
    }
	if( dir == RIGHT )
    {
	    y = randInt(room->y + 1, room->y + room->height);
        x = room->x + room->width;
        map[x][y] = CLOSED_DOOR;
		return {x + 1, y};
    }
	if( dir == UP )
    {
	    x = randInt(room->x + 1, room->x + room->width);
        y = room->y - 1;
        map[x][y] = CLOSED_DOOR;
		return {x, y - 1};
    }
	if( dir == DOWN )
    {
	    x = randInt(room->x + 1, room->x + room->width);
        y = room->y + room->height;
        map[x][y] = CLOSED_DOOR;
		return {x, y + 1};
    }
   
    return {0, 0};
}


void MapGenerator::createCorridors()
{
	for (int x = 0; x < horizontalRooms; x++) 
	{
        for (int y = 0; y < verticalRooms; y++) 
		{
            Room* room = &rooms[x][y];
            for (Room* otherRoom : room->connections) 
			{
                sf::Vector2i dir = getCardinalDirection(otherRoom->cellx - room->cellx, otherRoom->celly - room->celly);
                digPath(randomWallPosition(room, dir), randomWallPosition(otherRoom, opposite(dir) ));
            }
        }
    }
}

MapGenerator::MapGenerator(int horizontalRooms, int verticalRooms, int dungeonWidth, int dungeonHeight,
	int minRoomWidth, int maxRoomWidth, int minRoomHeight, int maxRoomHeight)
	: horizontalRooms(horizontalRooms), verticalRooms(verticalRooms),
		dungeonWidth(dungeonWidth), dungeonHeight(dungeonHeight), 
		minRoomWidth(minRoomWidth), maxRoomWidth(maxRoomWidth), 
		minRoomHeight(minRoomHeight), maxRoomHeight(maxRoomHeight)
{
}

bool MapGenerator::contains( Room* a, Room* b)
{
	return std::find(a->connections.begin(), a->connections.end(), b) != a->connections.end();
}

sf::Vector2i MapGenerator::opposite(const sf::Vector2i& dir)
{
	if( dir == UP) return DOWN;
	if( dir == DOWN) return UP;
	if( dir == LEFT) return RIGHT;
	if( dir == RIGHT) return LEFT;

	return dir;
}
