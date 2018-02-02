#pragma once
#include "Screen.h"
#include "Util.h"
#include <memory>
#include <TGUI/TGUI.hpp>
#include "CameraManager.h"
using namespace tgui;

class sf::RenderWindow;

class MainMenuScreen : public Screen
{

public:
	MainMenuScreen( Game* game, sf::RenderWindow& window );
	~MainMenuScreen() override;
	void show() override;
	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	void hide() override;
	void resized(float width, float height) override;


	void handleEvent(sf::Event& event) override;
private:
	std::unique_ptr<Gui> gui;
	std::shared_ptr<ChildWindow> cWindow;
	CameraManager manager;

	void exitGameCall();
	void newGameCall();
};
