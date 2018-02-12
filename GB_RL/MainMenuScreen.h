#pragma once
#include "Screen.h"
#include "Util.h"
#include <memory>
#include <TGUI/TGUI.hpp>
#include "CameraManager.h"

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
	std::unique_ptr<tgui::Gui> gui;
	std::shared_ptr<tgui::ChildWindow> cWindow;
	CameraManager manager;

	void exitGameCall();
	void newGameCall();
};
