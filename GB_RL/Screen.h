#pragma once

#include <SFML/Graphics.hpp>

class Game;

class Screen
{
public:
	Screen( Game* game );
	virtual ~Screen();

	virtual void show();
	virtual void update( float deltaTime  );
	virtual void draw( sf::RenderWindow& window);
	virtual void hide();
	virtual void resized( float width, float height);
	virtual void handleEvent(sf::Event& event) = 0;

protected:
	Game* game = nullptr;
};
