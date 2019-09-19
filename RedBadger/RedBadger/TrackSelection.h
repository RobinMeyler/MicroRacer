#pragma once
#include "SFML/Graphics.hpp"
#include "ResourceManager.h"
#include "GUI.h"

class TrackSelection
{
public:
	TrackSelection(ResourceManager & t_gameAssets);
	~TrackSelection();

	void initialize();
	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow & t_window);
	void handleControllerInput();

private:

	sf::Sprite m_mapImage;
	sf::Text m_mapNames[6];
	ResourceManager * ptrGameAsstes;
	
	GUI m_GUI;
};