#pragma once

#include <vector>

class Map;
class MapTile;
using Path = std::vector<MapTile*>;

/*!
 * \brief Contains functions to calculate paths across a map.
 */
class PathFinder
{
public:
	/*!
	 * \brief Calculate a least-cost path from start to goal across map.  The
	 *			algorithm is based on the A* method.
	 * \param map	Map to calculate the path on
	 * \param start	Starting tile for the path (Will not be included in the path)
	 * \param goal	Ending tile for the path (Always the last tile in the path if one exists)
	 */
	static Path findPath( Map* map, MapTile* start, MapTile* goal );

private:
	/* Do a simple manhattan distance calculation between point a and b.*/
	static double heuristic( MapTile* a, MapTile* b);

};
