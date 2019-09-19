#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "GUIGlobals.h"
#include "GUI.h"
#include "Xbox360Controller.h"
#include "ResourceManager.h"

class SoundOptions
{
public:
	SoundOptions(ResourceManager & t_gameAssets);
	~SoundOptions();
	void clearGUI();
	void initialize();
	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow & t_window);
	void handleControllerInput();
	void runAction(std::string & t_actionString);

private:
	ResourceManager * ptrGameAssets;

	sf::Font m_font;
	sf::Font m_digitFont;
	GUI m_GUI;

	sf::Sprite m_bckGroundSprite;
	sf::RectangleShape m_volumeLevelRectangle;
	sf::Text m_volumeText;
	int m_count{ 0 };

};

