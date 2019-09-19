#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "GUIGlobals.h"

#include "GUI.h"
#include "Label.h"
#include "Xbox360Controller.h"

#include "ResourceManager.h"

class Splash
{
public:
	Splash(ResourceManager & t_gameAssets);
	~Splash();

	void initialize();
	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow & t_window);
	void handleControllerInput();
	void runAction(std::string & t_actionString);

	void displayLogo();

private:
	int m_count{ 0 };

	sf::Sprite m_redLogo;
	sf::Texture m_redLogoTexture;

	sf::SoundBuffer m_soundBuffer;
	sf::Sound m_sound;


};

