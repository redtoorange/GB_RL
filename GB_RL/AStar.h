#pragma once

#include <vector>

class Map;
class MapTile;
using Path = std::vector<MapTile*>;

class AStar
{
public:
	static Path findPath( Map* map, MapTile* start, MapTile* goal );

private:
	static double heuristic( MapTile* a, MapTile* b);

};
