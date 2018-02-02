#include "CameraManager.h"


CameraManager::CameraManager(const sf::Vector2u& designedsize, const sf::Vector2f& center, const sf::Vector2f& size)
	:designedsize(designedsize), currentView(center, size)
{
	current = center;
	target = center;
}


void CameraManager::setCenter(const sf::Vector2f& pos)
{
	current = pos;
	target = pos;
	currentView.setCenter(pos);
}


sf::View& CameraManager::getView()
{
	return currentView;
}

void CameraManager::resized(unsigned int width, unsigned int height)
{
	currentView = calcView( {width, height} );
}

sf::View CameraManager::calcView( const sf::Vector2u &windowsize )
{
	sf::FloatRect viewport(0.f, 0.f, 1.f, 1.f);

	float screenwidth = windowsize.x / static_cast<float>(designedsize.x);
	float screenheight = windowsize.y / static_cast<float>(designedsize.y);

	if (screenwidth > screenheight)
	{
		viewport.width = screenheight / screenwidth;
		viewport.left = (1.f - viewport.width) / 2.f;
	}
	else if (screenwidth < screenheight)
	{
		viewport.height = screenwidth / screenheight;
		viewport.top = (1.f - viewport.height) / 2.f;
	}

	sf::View view(sf::FloatRect(0, 0, designedsize.x, designedsize.y));
	view.setViewport(viewport);

	return view;
}


void CameraManager::update(float delta)
{
	current.x = (smoothing * current.x) + ((1.0f - smoothing) * target.x);
	if (abs(current.x - target.x) <= threshold) current.x = target.x;

	current.y = (smoothing * current.y) + ((1.0f - smoothing) * target.y);
	if (abs(current.y - target.y) <= threshold) current.y = target.y;

	currentView.setCenter(current);
}

void CameraManager::setTarget(const sf::Vector2f& pos)
{
	target = pos;
}
