#include "Screen.h"
#include <iostream>


Screen::Screen(Game* game)
	:game(game)
{
}

Screen::~Screen()
{
	std::cout << "Deleted Screen\n";
}

void Screen::show()
{
}

void Screen::update( float deltaTime)
{
}

void Screen::draw(sf::RenderWindow& window)
{
}

void Screen::hide()
{
}

void Screen::resized(float width, float height)
{
}
