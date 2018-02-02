#ifndef UTIL_H
#define UTIL_H

#include <SFML/Graphics.hpp>

constexpr unsigned int WINDOW_WIDTH = 800;
constexpr unsigned int WINDOW_HEIGHT = 600;

const unsigned int GB_WINDOW_WIDTH = 160 * 4;
const unsigned int GB_WINDOW_HEIGHT = 144 * 4;

const sf::Vector2i UP{0, -1};
const sf::Vector2i DOWN{0, 1};
const sf::Vector2i LEFT{-1, 0};
const sf::Vector2i RIGHT{1, 0};

sf::Vector2f lerp(const sf::Vector2f& a, const  sf::Vector2f& b, float f);
float distance(const sf::Vector2f& a, const  sf::Vector2f& b);

int randInt(int min, int max);
int nextInt(int max);


#endif