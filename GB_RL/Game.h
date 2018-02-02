#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class Screen;

enum class ScreenType : uint32_t
{
	MAIN_MENU,
	PLAYING
};

class Game
{
public:
	Game();

	void begin();
	void update(float delta);
	void draw();
	void processInput();
	
	void setCurrentScreen( Screen* s);
	void setCurrentScreen( ScreenType screen );

	bool isRunning() const;
	void setRunning( bool run );

	sf::RenderWindow& getRenderWindow();


private:
	sf::RenderWindow window;
	sf::Clock clock;
	float frames;
	float elapsed;

	bool running;
	Screen* currentScreen = nullptr;
	std::map < ScreenType, std::unique_ptr<Screen> > screens;
};
