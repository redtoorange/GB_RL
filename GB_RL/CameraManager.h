#pragma once
#include <SFML/Graphics.hpp>


class CameraManager
{
public:
	CameraManager(const sf::Vector2u& designedsize, const sf::Vector2f& center = {0,0}, const sf::Vector2f& size = { 0,0 });
	
	void update(float delta);

	void setCenter(const sf::Vector2f& pos );
	void setTarget(const sf::Vector2f& pos );

	void resized(unsigned int width, unsigned int height);
	sf::View calcView(const sf::Vector2u &windowsize );
	sf::View& getView();

private:
	sf::Vector2f current;
	sf::Vector2f target;


	sf::Vector2u designedsize;
	sf::View currentView;

	float smoothing = 0.95f;
	float threshold = 0.05f;
};
