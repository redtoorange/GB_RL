#include "MainMenuScreen.h"

#include "Game.h"
#include <iostream>
using namespace tgui;

MainMenuScreen::MainMenuScreen(Game* game, sf::RenderWindow& window)
	: Screen(game), manager({GB_WINDOW_WIDTH, GB_WINDOW_HEIGHT})
{
	gui = make_unique<Gui>(window);

	auto vLayout = VerticalLayout::create({"50%", "50%"});

	cWindow = ChildWindow::create("Main Menu");
	cWindow->setSize({150, 150});

	auto newGame = Button::create("New");
	//	newGame->setSize({150, 50});
	//	newGame->setPosition({0, 0});
	newGame->connect("pressed", &MainMenuScreen::newGameCall, this);

	auto loadGame = Button::create("Load");
	//	loadGame->setSize({150, 50});
	//	loadGame->setPosition({0, 50});

	auto exitGame = Button::create("Exit");
	//	exitGame->setSize({150, 50});
	//	exitGame->setPosition({0, 100});
	exitGame->connect("pressed", &MainMenuScreen::exitGameCall, this);

	vLayout->add(newGame);
	vLayout->add(loadGame);
	vLayout->add(exitGame);
	//	cWindow->add(vLayout);
	gui->add(vLayout);
	//	vLayout->setPosition({(vLayout->getSize().x / 2 - GB_WINDOW_WIDTH), (GB_WINDOW_HEIGHT - vLayout->getSize().y) / 2  });
	vLayout->setPosition("(parent.size - size) / 2");
	//	vLayout->setPosition({100, 100 });
	//	gui->add(cWindow);
	gui->setView(manager.getView());
}

void MainMenuScreen::exitGameCall()
{
	game->setRunning(false);
}


void MainMenuScreen::newGameCall()
{
	game->setCurrentScreen(ScreenType::PLAYING);
}

MainMenuScreen::~MainMenuScreen()
{
}

void MainMenuScreen::show()
{
}

void MainMenuScreen::update(float deltaTime)
{
}

void MainMenuScreen::draw(sf::RenderWindow& window)
{
	gui->draw();
}

void MainMenuScreen::hide()
{
}

void MainMenuScreen::resized(float width, float height)
{
	manager.resized(width, height);
	gui->setView(manager.getView());
}

void MainMenuScreen::handleEvent(sf::Event& event)
{
	if (event.type == sf::Event::Resized)
	{
		resized(static_cast<float>(event.size.width), static_cast<float>(event.size.height));
	}
	gui->handleEvent(event);
}
