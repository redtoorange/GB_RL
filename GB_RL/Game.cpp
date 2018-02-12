#include "Game.h"
#include "Util.h"
#include "MainMenuScreen.h"
#include "GameScreen.h"
#include <iostream>

Game::Game()
	:window( sf::VideoMode{WINDOW_WIDTH, WINDOW_HEIGHT}, "SFML Window")
{
	window.setFramerateLimit(144);
	screens.emplace(ScreenType::PLAYING, make_unique<GameScreen>(this));
	screens.emplace(ScreenType::MAIN_MENU, make_unique<MainMenuScreen>(this, window));

	// Start game with the main menu or straight into the game
//	setCurrentScreen(ScreenType::MAIN_MENU);
	setCurrentScreen(ScreenType::PLAYING);
}

void Game::setCurrentScreen( Screen* s)
{
	currentScreen = s;
	s->resized(window.getSize().x, window.getSize().y);
}


void Game::setCurrentScreen(ScreenType screen)
{
	if( screens.find(screen) != screens.end() )
	{
		setCurrentScreen(screens[screen].get());
	}
}

void Game::update(float delta )
{
	

	// Do the updating
	currentScreen->update(delta);
}

void Game::draw()
{
	window.clear(sf::Color{74, 74, 74, 255});

	// Do the drawing
	currentScreen->draw( window );

	window.display();
}

void Game::processInput()
{
	sf::Event event;

	while( window.pollEvent(event))
	{
		// Process the events
		currentScreen->handleEvent(event);

		if( event.type == sf::Event::Closed || (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape))
			running = false;
	}
}


void Game::begin()
{
	running = true;
	frames = 0;
	elapsed = 0;

	while( running )
	{
		float delta = clock.restart().asSeconds();
		processInput();
		update(delta);
		draw();

		elapsed += delta;
		frames++;
		if(elapsed > 1.0f)
		{
			std::cout << "FPS: " << frames << endl;
			frames = 0;
			elapsed = 0;
		}
	}

	window.close();
}


bool Game::isRunning() const
{
	return running;
}

void Game::setRunning(bool run)
{
	running = run;
}


sf::RenderWindow& Game::getRenderWindow()
{
	return window;
}
