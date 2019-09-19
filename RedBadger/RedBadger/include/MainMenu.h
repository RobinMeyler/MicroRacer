#pragma once

#include <iostream>

#include <fstream>
#include <string>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "GUIGlobals.h"
#include "ResourceManager.h"
#include "GUI.h"
#include "Xbox360Controller.h"



class MainMenu
{
public:
	//MainMenu();
	MainMenu(ResourceManager & t_gameAssets);
	~MainMenu();
	void clearGUI();
	void initialize();
	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow & t_window);
	void handleControllerInput();
	void runAction(std::string & t_actionString);
	

	void setupSahder();
private:

	ResourceManager * ptrGameAssets;

	int m_count{ 0 };
	float m_rotate{ 3 };
	GUI m_gui;
	
	sf::Font m_font;

	sf::SoundBuffer m_wheelTurnBuffer;
	sf::Sound m_wheelTurnSFX;
	sf::SoundBuffer m_confirmBuffer;
	sf::Sound m_confirmSFX;


	sf::Sprite m_wheel;
	sf::Sprite m_body;

	sf::Sprite renderSprite;
	sf::RenderTexture renderTexture;
	sf::Texture distortionMap;
	sf::Shader shader1;
	float distortionFactor = .015f;
	float riseFactor = .15f;
	sf::Clock clock;
};

