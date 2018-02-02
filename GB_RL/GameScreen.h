#pragma once
#include "Screen.h"
#include "AssetManager.h"
#include "EnemyManager.h"
#include "CameraManager.h"
#include "Util.h"

class GameScreen : public Screen
{
public:
	GameScreen( Game* game);
	~GameScreen() override;

	void show() override;
	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	void hide() override;
	void resized(float width, float height) override;

	CameraManager* getCamameraManager();

	void handleEvent(sf::Event& event) override;
private:
	CameraManager gb_view;

	unique_ptr<Map> tileMap;
	unique_ptr<Player> player;

	AssetManager asset_manager;
	EnemyManager enemy_manager;
};
