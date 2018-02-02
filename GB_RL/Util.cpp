#include "Util.h"
#include "MapGenerator.h"

// Linearly interpolate between two vectors by a factor of f
sf::Vector2f lerp(const sf::Vector2f& a, const  sf::Vector2f& b, float f)
{
    return {a.x + f * (b.x - a.x),
		 a.y + f * (b.y - a.y)};
}

// Calculate the distance between two vectors
float distance(const sf::Vector2f& a, const  sf::Vector2f& b)
{
		float x_d = b.x - a.x;
		float y_d = b.y - a.y;
		return sqrt(x_d * x_d + y_d * y_d);
}

int randInt(int min, int max)
{
	return min + (rand() % (max - min + 1));
}



int nextInt(int max)
{
	return  (rand() % max);
}