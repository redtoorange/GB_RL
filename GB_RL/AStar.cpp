#include "AStar.h"

#include "MapTile.h"
#include <unordered_map>
#include <queue>
#include <functional>
#include <iostream>
using namespace std;

double AStar::heuristic( MapTile* a, MapTile* b)
{
	auto aPos = a->getGridPos();
	auto bPos = b->getGridPos();

	return abs(aPos.x - bPos.x) + abs(aPos.y - bPos.y);
}

typedef pair<MapTile*, float> PQ_Element;
bool operator<( const PQ_Element& l, const PQ_Element& r)
{
	return l.second < r.second;
}

Path AStar::findPath(Map* map, MapTile* start, MapTile* goal)
{
	unordered_map<MapTile*, MapTile*> cameFrom;
	unordered_map<MapTile*, double> costSoFar;

	priority_queue< PQ_Element, vector<PQ_Element>, greater<PQ_Element>> frontier;
	frontier.emplace( start, 0.0f );

	cameFrom[start] = start;
	costSoFar[start] = 0;

	while( !frontier.empty() )
	{
		MapTile* current = frontier.top().first;
		frontier.pop();

		if( current == goal) break;
		
		for( MapTile* next : current->getNeighbors() )
		{
			if ( !next->isWall() || next == goal  )
			{
				double newCost = costSoFar[current] + next->getCost();
				if (!costSoFar.count(next) || newCost < costSoFar[next])
				{
					costSoFar[next] = newCost;
					double priority = newCost + heuristic(next, goal);
					frontier.emplace(next, priority);
					cameFrom[next] = current;
				}
			}			
		}
	}

	Path path;

	if( cameFrom.find(goal) == cameFrom.end())
	{
		cout << "No path Found\n";
		return path;
	}
	MapTile* current = goal;

	while( current != start )
	{
		path.push_back(current);
		current = cameFrom[current];
	}

	path.push_back(start);
	reverse(path.begin(), path.end());

	return path;
}
